#ifndef _CANOPEN_PDO_MESSAGE_H_
#define _CANOPEN_PDO_MESSAGE_H_

#include "message.h"

namespace CANopen {
class PDOMessage : public Message
{
public:
    PDOMessage() = default;
    PDOMessage(const can_frame& other);
};
}

#endif // _CANOPEN_PDO_MESSAGE_H_
