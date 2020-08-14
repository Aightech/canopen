#include "emcy.h"

namespace CANopen {
EMCYMessage::EMCYMessage(const can_frame& other)
    : Message(other)
{
}


uint16_t
EMCYMessage::code() const
{
	return data[0] + (data[1] << 8);
}

uint8_t
EMCYMessage::reg() const
{
	return data[2];
}
}
