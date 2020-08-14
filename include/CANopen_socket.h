#ifndef _CANOPEN_SOCKET_H_
#define _CANOPEN_SOCKET_H_

/*!
 * \file canopen_socket.h
 * \brief Canopen object able to send command through a CAN interface using the UNIX socket.
 * \author Alexis Devillard
 * \version 1.0
 */

#include <memory>
#include <string>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <mutex>
#include <initializer_list>

#include "message.h"
#include "payload.h"
#include "sdo.h"
#include "pdo.h"
#include "nmt.h"
#include "emcy.h"


#define IF_VERBOSE(lvl, cmd, m_lvl)      \
    if (m_lvl >= lvl) { \
        CANopen::g_verbose_mutex.lock(); \
        cmd;                      \
        CANopen::g_verbose_mutex.unlock(); \
    }


namespace CANopen {
extern std::mutex g_verbose_mutex;
/*! \class Socket
 * \brief Canopen object able to send command through a CAN interface using UNIX sockets.
 */
class Socket {
public:
    /*!
     *  \brief Constructor
     *  \param ifname : Name of the can interface ex:"can0"
     *  \param verbose : Display the different message sent.
     */
    Socket(std::string ifname, int verbose_level = 0);

    /*!
     *  \brief Constructor
     *  \param ifname : Name of the can interface ex:"can0"
     *  \param cob_id : Filtering only frame with this ID.
     *  \param verbose : Display the different message sent.
     */
    Socket(std::string ifname, uint32_t cob_id, int verbose_level = 0);

  
  
  void add_filter(std::initializer_list<struct can_filter> rfilter);
  
    /*!
     *  \brief return true if the can interface is successfully bound
     */
    int bind();

    /*!
     *  \brief Function to send a CAN message.
     *  \param msg : CAN frame to send
     */
    void send(const Message&& msg);

    std::shared_ptr<Message> receive();

private:
    int m_socket; /*!< Can socket */
    std::string m_ifname; /*!< CAN interface name*/

    int m_verbose_level; /*!< Verbose mode*/
};
}

#endif // _CANOPEN_SOCKET_H_
