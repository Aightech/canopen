#include "CANopen_socket.h"
#include <iostream>
#include <linux/can/raw.h>
#include <net/if.h>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>



namespace CANopen {
std::mutex g_verbose_mutex;

Socket::Socket(std::string ifname, int verbose_level)
    : m_ifname(ifname), m_verbose_level(verbose_level) {
    if((m_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
        throw std::runtime_error(std::string("Error while opening socket: ") + strerror(errno));

    int r = 0;
    if((r = bind()) < 0) {
        throw std::runtime_error(std::string("Failed to bind socket: ") + strerror(-r));
    }

//    struct timeval tv;
//    tv.tv_sec = 1;
//    tv.tv_usec = 0;
//    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv);
}

Socket::Socket(std::string ifname, uint32_t cob_id, int verbose_level)
    : Socket(ifname, verbose_level) {
    struct can_filter rfilter[1];

    rfilter[0].can_id = cob_id;
    rfilter[0].can_mask = CAN_SFF_MASK;
    setsockopt(m_socket, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
};

void
Socket::add_filter(std::initializer_list<struct can_filter> rfilter_) {
    struct can_filter rfilter[rfilter_.size()];
    int i=0;
    for(auto filter :rfilter_)
    {
        rfilter[i].can_id = filter.can_id;
        rfilter[i++].can_mask = filter.can_mask;//CAN_SFF_MASK;
    }
	

    setsockopt(m_socket, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
};

int
Socket::bind() {
    struct ifreq ifr;
    strcpy(ifr.ifr_name, m_ifname.c_str());
    if(ioctl(m_socket, SIOCGIFINDEX, &ifr) < 0) {
        return -errno;
    } else {
        struct sockaddr_can addr;
        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        IF_VERBOSE(1, std::cout << m_ifname << " at index " << ifr.ifr_ifindex << std::endl, m_verbose_level)

        if(::bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
            return -errno;
    }
    return 0;
}

void
Socket::send(const Message &&msg) {
    int32_t n = write(m_socket, msg, sizeof(struct can_frame));
    if(n < static_cast<ssize_t>(sizeof(struct can_frame))) {
        throw std::runtime_error("Failed to send message (n=" + std::to_string(n) + ")");
    }
}

std::shared_ptr<Message>
Socket::receive() {
    Message ans;
    int32_t n = read(m_socket, ans, sizeof(struct can_frame));
	

    if(n < 0) {
        IF_VERBOSE(1, std::cout << "CANopen::Socket::receive: nothing to read" << std::endl, m_verbose_level)
        return std::shared_ptr<Message>();
    } else if(n < static_cast<ssize_t>(sizeof(struct can_frame))) {
        IF_VERBOSE(1, std::cerr << "CANopen::Socket::receive: incomplete CAN frame" << std::endl, m_verbose_level)
        return std::shared_ptr<Message>();
    }

    std::shared_ptr<Message> ret;
    switch(ans.function_code()) {
    case Message::NMT:
        ret = std::make_shared<NMTMessage>(ans);
        break;
    case Message::Emergency:
        if(ans.node_id() == 0) { // Sync frame
        } else {                 // Emergency frame
            ret = std::make_shared<Message>(ans);
        }
        break;
    case Message::TimeStamp:
        ret = std::make_shared<Message>(ans);
        break;
    case Message::PDO1Transmit:
    case Message::PDO2Transmit:
    case Message::PDO3Transmit:
    case Message::PDO4Transmit:
    case Message::PDO1Receive:
    case Message::PDO2Receive:
    case Message::PDO3Receive:
    case Message::PDO4Receive:
        ret = std::make_shared<PDOMessage>(ans);
        break;
    case Message::SDOTransmit:
        ret = std::make_shared<SDOInbound>(ans);
        break;
    case Message::SDOReceive:
        break;
    case Message::Heartbeat:
        ret = std::make_shared<Message>(ans);
        break;
    }

    return ret;
}
} // namespace CANopen
