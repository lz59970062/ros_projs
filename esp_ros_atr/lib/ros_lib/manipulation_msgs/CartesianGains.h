#ifndef _ROS_manipulation_msgs_CartesianGains_h
#define _ROS_manipulation_msgs_CartesianGains_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace manipulation_msgs
{

  class CartesianGains : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t gains_length;
      typedef float _gains_type;
      _gains_type st_gains;
      _gains_type * gains;
      uint32_t fixed_frame_length;
      typedef float _fixed_frame_type;
      _fixed_frame_type st_fixed_frame;
      _fixed_frame_type * fixed_frame;

    CartesianGains():
      header(),
      gains_length(0), st_gains(), gains(nullptr),
      fixed_frame_length(0), st_fixed_frame(), fixed_frame(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->gains_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->gains_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->gains_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->gains_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->gains_length);
      for( uint32_t i = 0; i < gains_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->gains[i]);
      }
      *(outbuffer + offset + 0) = (this->fixed_frame_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->fixed_frame_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->fixed_frame_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->fixed_frame_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->fixed_frame_length);
      for( uint32_t i = 0; i < fixed_frame_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->fixed_frame[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t gains_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      gains_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      gains_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      gains_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->gains_length);
      if(gains_lengthT > gains_length)
        this->gains = (float*)realloc(this->gains, gains_lengthT * sizeof(float));
      gains_length = gains_lengthT;
      for( uint32_t i = 0; i < gains_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_gains));
        memcpy( &(this->gains[i]), &(this->st_gains), sizeof(float));
      }
      uint32_t fixed_frame_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      fixed_frame_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      fixed_frame_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      fixed_frame_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->fixed_frame_length);
      if(fixed_frame_lengthT > fixed_frame_length)
        this->fixed_frame = (float*)realloc(this->fixed_frame, fixed_frame_lengthT * sizeof(float));
      fixed_frame_length = fixed_frame_lengthT;
      for( uint32_t i = 0; i < fixed_frame_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_fixed_frame));
        memcpy( &(this->fixed_frame[i]), &(this->st_fixed_frame), sizeof(float));
      }
     return offset;
    }

    virtual const char * getType() override { return "manipulation_msgs/CartesianGains"; };
    virtual const char * getMD5() override { return "ab347f046ca5736a156ec424cbb63635"; };

  };

}
#endif
