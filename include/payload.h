#ifndef _CANOPEN_PAYLOAD_H_
#define _CANOPEN_PAYLOAD_H_

/*!
 * \file payload.h
 * \brief  Payload of CANopen message: array of 1 to 8 bytes of data.
 * \author Florian Richer & Alexis Devillard
 * \version 1.0
 */

#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace CANopen {
/*!
 * \brief Payload of CANopen message: array of 1 to 8 bytes of data
 */
class Payload : public std::vector<uint8_t> {
    public:
    Payload() = default;
    Payload(const Payload &) = default;
    Payload(const std::vector<uint8_t> &other);

    template <typename T>
    /*!
     * \brief Payload Constructor from a standard data type variable. It transfrom the n bytes of the data into a array of n bytes.
     * \param value The variable to store in the payload
     */
    Payload(T value) {
        for(int i = 0; i < sizeof(T); i++)
            push_back(*((uint8_t *)(&value) + i));
    }

    Payload &
    operator=(const Payload &) = default;

    template <typename T>
    /*!
     * \brief value Returns the data casted  as a variable of type T
     * \param begin The index of the data array from where the data must be returned.
     * \return The data as a variable of type T.
     */
    T &
    value(unsigned begin = 0) {
        if(empty())
            throw std::runtime_error(std::string("Empty payload."));
        return *(T *)(data() + begin);
    };


    template <typename T>
    /*!
     * \brief operator << Adds a variable inside the payload
     * \param value The variable to store
     * \return The Payload reference.
     */
    Payload &
    operator<<(T &&value) {
        for(int i = 0; i < sizeof(T); i++)
            push_back(*((uint8_t *)(&value) + i));
        return *this;
    };
    
    /*!
     * \brief operator << Adds a variable inside the payload
     * \param p The variable to store
     * \return The Payload reference.
     */
    Payload &
    operator<<(Payload &&p) {
        for(int i = 0; i < p.size(); i++)
            push_back(*((uint8_t *)(&p[i])));
        return *this;
    };
    
    /*!
     * \brief store_at Stores a variable at a specified index in the data array.
     * \param p The variable to store.
     * \param slot The index in data array where the variable has to be store to.
     * \return
     */
    Payload &
    store_at(Payload &&p, int slot) {
    	for(int i = this->size(); i < slot ; i++)
    		this->push_back(0);
        for(int i = slot; i < slot + p.size(); i++)
        {
        	if(i < this->size())
        		(*this)[i]=*((uint8_t *)(&p[i]));
        	else
            		this->push_back(*((uint8_t *)(&p[i-slot])));
         }
        return *this;
    };

    operator std::string() const;
};
} // namespace CANopen

std::ostream &
operator<<(std::ostream &out, const CANopen::Payload &p);

#endif // _CANOPEN_PAYLOAD_H_
