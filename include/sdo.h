#ifndef _CANOPEN_SDO_MESSAGE_H_
#define _CANOPEN_SDO_MESSAGE_H_

#include "message.h"

namespace CANopen {
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

    uint16_t
    index() const;
    
    bool is_confirmation()
    {
    	if(data[0]==0x60)
    		return true;
    	else
    		return false;
    };
    bool is_error()
    {
    	if(data[0]==0x80)
    		return true;
    	else
    		return false;
    };

    uint8_t
    subindex() const;

    uint32_t
    index__sub() const;

    uint32_t
    id() const{
        return index__sub();
    }
    
    uint8_t 
    size_data() const;

    Payload
    payload() const;
};

class SDOInbound : public SDOMessage {
    public:
    SDOInbound(const can_frame &other);
};

class SDOOutbound : public SDOMessage {
    public:
    SDOOutbound(uint8_t node_id, RDWR dir, uint16_t index, uint8_t subindex, Payload payload);
};

class SDOOutboundRead : public SDOOutbound {
    public:
    SDOOutboundRead(uint8_t node_id, uint16_t index, uint8_t subindex);
    SDOOutboundRead(uint8_t node_id, uint32_t index__sub);
};

class SDOOutboundWrite : public SDOOutbound {
    public:
    SDOOutboundWrite(uint8_t node_id, uint16_t index, uint8_t subindex, Payload payload);
    SDOOutboundWrite(uint8_t node_id, uint32_t index__sub, Payload payload);
};
} // namespace CANopen

#endif // _CANOPEN_SDO_MESSAGE_H_
