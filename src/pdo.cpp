#include "pdo.h"

namespace CANopen {
PDOMessage::PDOMessage(const can_frame& other)
    : Message(other)
{
}

PDOMessage::PDOMessage(PDOFunctionCode fn, uint8_t node_id, Payload payload)
    : Message(fn + node_id, payload)
{
}

}
