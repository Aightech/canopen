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

#include "message.h"
#include "payload.h"
#include "sdo.h"
#include "pdo.h"
#include "nmt.h"

#define IF_VERBOSE(lvl, cmd)      \
    if (m_verbose_level >= lvl) { \
        cmd;                      \
    }

namespace CANopen {
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