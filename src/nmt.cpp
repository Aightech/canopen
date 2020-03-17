#include "nmt.h"

namespace CANopen {
NMTMessage::NMTMessage(const can_frame& other)
    : Message(other)
{
}

NMTMessage::NMTMessage(Code code, uint8_t node_id) : Message(0,Payload({code,node_id}))
{
}
}
