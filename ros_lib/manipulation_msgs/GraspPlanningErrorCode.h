#ifndef _ROS_manipulation_msgs_GraspPlanningErrorCode_h
#define _ROS_manipulation_msgs_GraspPlanningErrorCode_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace manipulation_msgs
{

  class GraspPlanningErrorCode : public ros::Msg
  {
    public:
      typedef int32_t _value_type;
      _value_type value;
      enum { SUCCESS =  0 };
      enum { TF_ERROR =  1 };
      enum { OTHER_ERROR =  2 };

    GraspPlanningErrorCode():
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_value.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_value.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_value.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->value = u_value.real;
      offset += sizeof(this->value);
     return offset;
    }

    virtual const char * getType() override { return "manipulation_msgs/GraspPlanningErrorCode"; };
    virtual const char * getMD5() override { return "d0cbf262cc3d8075a46b994eef1bdb2a"; };

  };

}
#endif
