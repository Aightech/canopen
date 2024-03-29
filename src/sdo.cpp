#include "sdo.h"

#include <stdexcept>
#include <iostream>

namespace CANopen {
SDOMessage::SDOMessage(const can_frame &other)
    : Message(other) {
}

SDOMessage::SDOMessage(FunctionCode fn, uint8_t node_id, CCS spec, uint8_t n, uint8_t e, uint8_t s, uint16_t index, uint8_t subindex, Payload payload) {
    if(fn != SDOReceive && fn != SDOTransmit) {
        throw std::runtime_error("SDOMessage: wrong function code(" + (static_cast<std::stringstream const &>(std::stringstream() << "0x" << std::hex << fn)).str() + ")");
    }

    can_id = fn + node_id;
    can_dlc = CAN_MAX_DLC;
    data[0] = static_cast<uint8_t>(spec << 5 | (n&0x03) << 2 | e << 1 | s);
    data[1] = static_cast<uint8_t>(index);
    data[2] = static_cast<uint8_t>(index >> 8);
    data[3] = subindex;

    for(unsigned int i = 0; i < payload.size(); ++i) {
        data[4 + i] = payload[i];
    }
}

uint16_t
SDOMessage::index() const{
    return data[1] + (data[2] << 8);
}

uint8_t
SDOMessage::subindex() const{
    return data[3];
}

uint32_t
SDOMessage::index__sub() const{
    return ((data[1] + (data[2] << 8)) << 16) + data[3];
}

Payload
SDOMessage::payload() const{
    return Payload(std::vector<uint8_t>(data + 4, data + 4 + size_data()));
}

uint8_t 
SDOMessage::size_data() const
{
 return 4-(0x3&(data[0]>>2));
};

SDOInbound::SDOInbound(const can_frame &other)
    : SDOMessage(other) {
}

SDOOutbound::SDOOutbound(uint8_t node_id, RDWR dir, uint16_t index, uint8_t subindex, Payload payload)
    : SDOMessage(SDOReceive, node_id, dir == Write ? InitiateDownload : InitiateUpload, 4 - payload.size(), 1, 1, index, subindex, payload) {
}

SDOOutboundRead::SDOOutboundRead(uint8_t node_id, uint16_t index, uint8_t subindex)
    : SDOOutbound(node_id, Read, index, subindex, Payload()) {
}

SDOOutboundRead::SDOOutboundRead(uint8_t node_id, uint32_t index__sub)
    : SDOOutbound(node_id, Read, (uint16_t)(index__sub >> 16), (uint8_t)index__sub, Payload()) {
}

SDOOutboundWrite::SDOOutboundWrite(uint8_t node_id, uint16_t index, uint8_t subindex, Payload payload)
    : SDOOutbound(node_id, Write, index, subindex, payload) {
}

SDOOutboundWrite::SDOOutboundWrite(uint8_t node_id, uint32_t index__sub, Payload payload)
    : SDOOutbound(node_id, Write, (uint16_t)(index__sub >> 16), (uint8_t)index__sub, payload) {
}

} // namespace CANopen
