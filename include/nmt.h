#ifndef _CANOPEN_NMT_MESSAGE_H_
#define _CANOPEN_NMT_MESSAGE_H_

#include "message.h"

namespace CANopen {
class NMTMessage : public Message
{
public:
    enum Code : uint8_t{
        Initialising = 0,
        GoToOperational = 0x01,
        GoToStopped = 0x02,
        Stopped = 0x04,
        Operational = 0x05,
        PreOperational = 0x7f,
        GoToPreOperational = 0x80,
        GoToResetNode = 0x81,
        GoToResetCommunication = 0x82
    };

    NMTMessage() = default;
    NMTMessage(const can_frame& other);
    NMTMessage(Code code, uint8_t node_id);
};
}

#endif // _CANOPEN_NMT_MESSAGE_H_
