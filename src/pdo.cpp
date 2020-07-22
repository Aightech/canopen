#include "pdo.h"

namespace CANopen {
PDOMessage::PDOMessage(const can_frame &other)
    : Message(other) {
}

PDOMessage::PDOMessage(PDOFunctionCode fn, uint8_t node_id, Payload payload)
    : Message(fn + node_id, payload) {
}

uint8_t PDOMessage::num()
{
  return (function_code() >> 8)-1;
}

} // namespace CANopen
