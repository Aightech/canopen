#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <linux/can.h>
#include <string>
#include "payload.h"

namespace CANopen {
class Message : public can_frame {
public:
    enum FunctionCode: uint32_t {
        NMT = 0,
        Emergency = 0x80,
        Sync = 0x80,
        TimeStamp = 0x100,
        PDO1Transmit = 0x180,
        PDO1Receive = 0x200,
        PDO2Transmit = 0x280,
        PDO2Receive = 0x300,
        PDO3Transmit = 0x380,
        PDO3Receive = 0x400,
        PDO4Transmit = 0x480,
        PDO4Receive = 0x500,
        SDOTransmit = 0x580,
        SDOReceive = 0x600,
        Heartbeat = 0x700
    };

    Message() = default;
    Message(const can_frame& other);
    Message(uint32_t cob_id, Payload payload);
    
    operator can_frame*() const { return const_cast<can_frame*>(reinterpret_cast<const can_frame*>(&can_id));}; 

    FunctionCode function_code() const;
    uint8_t node_id() const;
    virtual  Payload payload() const;
    virtual uint32_t id() const {return 0;};//return index__sub if sdomsg or pdo number if pdomsg

    std::string to_string() const;
};
}

#endif // MESSAGE_H
