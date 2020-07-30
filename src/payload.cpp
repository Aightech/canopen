#include "payload.h"
#include <ostream>
#include <iomanip>

namespace CANopen {
Payload::Payload(const std::vector<uint8_t>& other)
    : std::vector<uint8_t>(other)
{
}

Payload::operator std::string() const
{
    std::stringstream ss;
    ss << "[" << std::hex << std::setfill('0') << std::uppercase;
    for (auto it = this->begin(); it < this->end(); ++it) {
      ss << std::setw(2) << (int)*it << ' ';
    }
    ss << ((size()==0)?"]":"\b]");
    
    return ss.str();
}
  
}

std::ostream& operator<<(std::ostream& out, const CANopen::Payload& p)
{
    return out << static_cast<std::string>(p);
}
