#ifndef MESSAGE_H
#define MESSAGE_H

/*!
 * \file message.h
 * \brief  CAN_frame message sent and received throught CANopen socket.
 * \author Florian Richer & Alexis Devillard
 * \version 1.0
 */

#include "payload.h"
#include <cstdint>
#include <linux/can.h>
#include <string>

namespace CANopen {
/*!
 * \brief can_frame object sent and received throught CANopen socket.
 */
class Message : public can_frame {
    public:
    /*!
     * \brief Function codes
     */
    enum FunctionCode : uint32_t {
        NMT = 0,              /*!<  **0<sub>h</sub>** NMT Message (Network management) */
        Emergency = 0x80,     /*!< **80<sub>h</sub>** EMCY Message (Emergency Object) */
        Sync = 0x80,          /*!< **80<sub>h</sub>**  */
        TimeStamp = 0x100,    /*!< **100<sub>h</sub>**  */
        PDO1Transmit = 0x180, /*!< **180<sub>h</sub>** PDO1 Transmiting Message (Process Data Object) */
        PDO1Receive = 0x200,  /*!< **200<sub>h</sub>** PDO1 Receiving Message (Process Data Object) */
        PDO2Transmit = 0x280, /*!< **280<sub>h</sub>** PDO2 Transmiting Message (Process Data Object) */
        PDO2Receive = 0x300,  /*!< **300<sub>h</sub>** PDO2 Receiving Message (Process Data Object)*/
        PDO3Transmit = 0x380, /*!< **380<sub>h</sub>** PDO3 Transmiting Message (Process Data Object) */
        PDO3Receive = 0x400,  /*!< **400<sub>h</sub>** PDO3 Receiving Message (Process Data Object) */
        PDO4Transmit = 0x480, /*!< **480<sub>h</sub>** PDO4 Transmiting Message (Process Data Object) */
        PDO4Receive = 0x500,  /*!< **500<sub>h</sub>** PDO4 Receiving Message (Process Data Object) */
        SDOTransmit = 0x580,  /*!< **580<sub>h</sub>** SDO Transmiting Message (Service Data Object)*/
        SDOReceive = 0x600,   /*!< **600<sub>h</sub>** SDO Receiving Message (Service Data Object) */
        Heartbeat = 0x700     /*!< **700<sub>h</sub>**  */
    };

    Message() = default;
    Message(const can_frame &other);
    Message(uint32_t cob_id, Payload payload);

    operator can_frame *() const { return const_cast<can_frame *>(reinterpret_cast<const can_frame *>(&can_id)); };

    /*!
     * \brief function_code
     * \return Returns the function code of the message (without the node id)
     */
    FunctionCode
    function_code() const;

    /*!
     * \brief node_id
     * \return Returns the ID of the node sending or getting the message (extracted from the COB ID)
     */
    uint8_t
    node_id() const;

    /*!
     * \brief payload
     * \return Returns the payload of the message.
     */
    virtual Payload
    payload() const;
    /*!
     * \brief id
     * \return Depends of the child class : return index__sub if SDOMessage or pdo number if PDOMessage
     */
    virtual uint32_t
    id() const { return 0; };

    std::string
    to_string() const;
};
} // namespace CANopen

#endif // MESSAGE_H
