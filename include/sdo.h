#ifndef _CANOPEN_SDO_MESSAGE_H_
#define _CANOPEN_SDO_MESSAGE_H_

/*!
 * \file sdo.h
 * \brief  SDO message sent and received throught CANopen socket.
 * \author Florian Richer & Alexis Devillard
 * \version 1.0
 */

#include "message.h"

namespace CANopen {
/*!
 * \brief SDO Message (Service Data Object)
 */
class SDOMessage : public Message {
    public:
    enum RDWR {
        Read,
        Write
    };

    enum CCS {
        SegmentDownload = 0,
        InitiateDownload = 1,
        InitiateUpload = 2,
        SegmentUpload = 3,
        AbortTransfer = 4,
        BlockUpload = 5,
        BlockDownload = 6
    };

    SDOMessage() = default;
    SDOMessage(const can_frame &other);
    SDOMessage(FunctionCode fn,
               uint8_t node_id,
               CCS spec,
               uint8_t n,
               uint8_t e,
               uint8_t s,
               uint16_t index,
               uint8_t subindex,
               Payload payload);

    /*!
     * \brief index
     * \return Returns the index of the register.
     */
    uint16_t
    index() const;
    
    /*!
     * \brief is_confirmation
     * \return  Returns true if the message is a confirmation from a previous SDO write message.
     */
    bool is_confirmation()
    {
    	if(data[0]==0x60)
    		return true;
    	else
    		return false;
    };

    /*!
     * \brief is_error
     * \return  Returns true if the message is an error sent throught SDO message.
     */
    bool is_error()
    {
    	if(data[0]==0x80)
    		return true;
    	else
    		return false;
    };

    /*!
     * \brief subindex
     * \return Returns the subindex of the register.
     */
    uint8_t
    subindex() const;

    /*!
     * \brief index__sub
     * \return Returns the index__sub of the register.
     */
    uint32_t
    index__sub() const;

    /*!
     * \brief id
     * \return Returns the index__sub of the register.
     */
    uint32_t
    id() const{
        return index__sub();
    }
    
    /*!
     * \brief size_data
     * \return Returns the size of the data stored in the message payload
     */
    uint8_t 
    size_data() const;

    /*!
     * \brief payload
     * \return Returns the message payload
     */
    Payload
    payload() const;
};

/*!
 * \brief SDO received Message.
 */
class SDOInbound : public SDOMessage {
    public:
    SDOInbound(const can_frame &other);
};

/*!
 * \brief SDO Message to be sent.
 */
class SDOOutbound : public SDOMessage {
    public:
    SDOOutbound(uint8_t node_id, RDWR dir, uint16_t index, uint8_t subindex, Payload payload);
};

/*!
 * \brief SDO Message to be sent to read the value from the object dictionary of a remote device.
 */
class SDOOutboundRead : public SDOOutbound {
    public:
    SDOOutboundRead(uint8_t node_id, uint16_t index, uint8_t subindex);
    SDOOutboundRead(uint8_t node_id, uint32_t index__sub);
};

/*!
 * \brief SDO Message to be sent to write the value of the object dictionary of a remote device.
 */
class SDOOutboundWrite : public SDOOutbound {
    public:
    SDOOutboundWrite(uint8_t node_id, uint16_t index, uint8_t subindex, Payload payload);
    SDOOutboundWrite(uint8_t node_id, uint32_t index__sub, Payload payload);
};
} // namespace CANopen

#endif // _CANOPEN_SDO_MESSAGE_H_
