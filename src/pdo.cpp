#include "pdo.h"

namespace CANopen {
PDOMessage::PDOMessage(const can_frame& other)
    : Message(other)
{
}
}
