#include "payload.h"
#include <ostream>

namespace CANopen {
Payload::Payload(const std::vector<uint8_t>& other)
    : std::vector<uint8_t>(other)
{
}

Payload::operator std::string() const
{
    std::stringstream ss;
    ss << std::hex << "0x";
    for (auto it = begin(); it < end(); ++it) {
        ss << *it;
    }
    return ss.str();
}
}

std::ostream& operator<<(std::ostream& out, const CANopen::Payload& p)
{
    return out << static_cast<std::string>(p);
}
