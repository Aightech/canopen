#ifndef _CANOPEN_PAYLOAD_H_
#define _CANOPEN_PAYLOAD_H_

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>

namespace CANopen {
class Payload : public std::vector<uint8_t> {
public:
    Payload() = default;
    Payload(const Payload&) = default;
    Payload(const std::vector<uint8_t>& other);
    Payload& operator=(const Payload&) = default;

    template <typename T>
    static Payload from_data(const T& value)
    {
        Payload ret;
        for (int i = 0; i < sizeof(T); ++i) {
            ret.push_back(value >> (8 * i));
        }
        return ret;
    }

    template <typename T1, typename... Ts>
    static Payload from_data(const T1& value, const Ts&&... others)
    {
        return from_data(others...).push_back(from_data(value));
    }

    template <typename T>
    Payload& operator>>(T& value)
    {
        if (sizeof(T) > size()) {
            throw std::runtime_error("Data type is bigger than payload");
        }

        value = 0;
        for (auto it = begin() + sizeof(T) - 1; it >= begin(); --it) {
            value |= *it;
            value <<= 8;
        }
        erase(begin(), begin() + sizeof(T));
        return *this;
    }

    operator std::string() const;
};
}

std::ostream& operator<<(std::ostream& out, const CANopen::Payload& p);

#endif // _CANOPEN_PAYLOAD_H_
