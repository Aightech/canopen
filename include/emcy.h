#ifndef _CANOPEN_EMCY_MESSAGE_H_
#define _CANOPEN_EMCY_MESSAGE_H_

#include "message.h"

namespace CANopen {
class EMCYMessage : public Message {
    public:

    EMCYMessage() = default;
    EMCYMessage(const can_frame &other);
    
   	uint16_t code() const;
   	uint8_t reg() const;
};
} // namespace CANopen

#endif // _CANOPEN_NMT_MESSAGE_H_
