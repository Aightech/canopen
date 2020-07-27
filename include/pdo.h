#ifndef _CANOPEN_PDO_MESSAGE_H_
#define _CANOPEN_PDO_MESSAGE_H_

#include "message.h"
#include "sdo.h"

namespace CANopen {
class PDOMessage : public Message {
    public:
    enum PDOFunctionCode : uint32_t {
        PDO1Transmit = Message::PDO1Transmit,
        PDO1Receive = Message::PDO1Receive,
        PDO2Transmit = Message::PDO2Transmit,
        PDO2Receive = Message::PDO2Receive,
        PDO3Transmit = Message::PDO3Transmit,
        PDO3Receive = Message::PDO3Receive,
        PDO4Transmit = Message::PDO4Transmit,
        PDO4Receive = Message::PDO4Receive,
    };

    PDOMessage() = default;
    PDOMessage(const can_frame &other);
    PDOMessage(PDOFunctionCode fn, uint8_t node_id, Payload payload);

    uint8_t
    num();

    uint32_t
    id() {
        return num();
    };
};
} // namespace CANopen

#endif // _CANOPEN_PDO_MESSAGE_H_
