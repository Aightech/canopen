#ifndef _CANOPEN_PAYLOAD_H_
#define _CANOPEN_PAYLOAD_H_

#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace CANopen {
class Payload : public std::vector<uint8_t> {
    public:
    Payload() = default;
    Payload(const Payload &) = default;
    Payload(const std::vector<uint8_t> &other);

    template <typename T>
    Payload(T value) {
        for(int i = 0; i < sizeof(T); i++)
            push_back(*((uint8_t *)(&value) + i));
    }

    Payload &
    operator=(const Payload &) = default;

    template <typename T>
    static Payload
    from_data(const T &value) {
        Payload ret;
        for(int i = 0; i < sizeof(T); ++i) {
            ret.push_back(value >> (8 * i));
        }
        return ret;
    }

    template <typename T1, typename... Ts>
    static Payload
    from_data(const T1 &value, const Ts &&... others) {
        return from_data(others...).push_back(from_data(value));
    }

    template <typename T>
    T &
    value(unsigned begin = 0) {
        if(empty())
            throw std::runtime_error(std::string("Empty payload."));
        return *(T *)(data() + begin);
    }

    template <typename T>
    Payload &
    operator<<(T &&value) {
        for(int i = 0; i < sizeof(T); i++)
            push_back(*((uint8_t *)(&value) + i));
        return *this;
    }

    operator std::string() const;
};
} // namespace CANopen

std::ostream &
operator<<(std::ostream &out, const CANopen::Payload &p);

#endif // _CANOPEN_PAYLOAD_H_
