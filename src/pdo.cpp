#include "pdo.h"

namespace CANopen {
PDOMessage::PDOMessage(const can_frame &other)
    : Message(other) {
}

PDOMessage::PDOMessage(PDOFunctionCode fn, uint8_t node_id, Payload payload)
    : Message(fn + node_id, payload) {
}

SDOOutboundWrite
PDOMessage::set(uint8_t node_id, PDOFunctionCode fn) {
    uint16_t index = 0;
    if((fn & 0x80) == 0x00) //T_PDO
    {
        index = (0x1400 + (fn >> 8) - 2);
    } else {
        index = (0x1800 + (fn >> 8) - 1);
    }
    return CANopen::SDOOutboundWrite(node_id, index, 1, 0x04000000 + fn + node_id);
}

} // namespace CANopen
