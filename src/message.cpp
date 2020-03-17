#include "message.h"
#include <sstream>
#include <string.h>

namespace CANopen {
Message::Message(uint32_t cob_id, Payload payload)
{
    can_id = cob_id;
    can_dlc = payload.size();
    memcpy(data, payload.data(), can_dlc);
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
    return std::vector<uint8_t>(data, data + can_dlc);
}

std::string Message::to_string()
{
    std::stringstream ss;
    ss << std::hex << "0x" << function_code() << " | 0x" << (int)node_id() << " | " << payload();
    return ss.str();
}
}
