#include "message.h"
#include <sstream>
#include <string.h>

namespace CANopen {
Message::Message(uint32_t cob_id, Payload payload)
{
    can_id = cob_id;
    can_dlc = CAN_MAX_DLC;
    memcpy(data, payload.data(), payload.size());
}

Message::Message(const can_frame& other)
    : can_frame(other)
{
}

Message::FunctionCode Message::function_code()
{
    return static_cast<FunctionCode>(can_id & 0xff80);
}

uint8_t Message::node_id()
{
    return can_id & 0x7f;
}

Payload Message::payload()
{
    return std::vector<uint8_t>(data, data + CAN_MAX_DLC);
}

std::string Message::to_string()
{
    std::stringstream ss;
    ss << std::hex << "0x" << function_code() << " | 0x" << node_id() << " | " << payload();
    return ss.str();
}
}
