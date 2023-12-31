#ifndef _ROS_household_objects_database_msgs_DatabaseReturnCode_h
#define _ROS_household_objects_database_msgs_DatabaseReturnCode_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace household_objects_database_msgs
{

  class DatabaseReturnCode : public ros::Msg
  {
    public:
      typedef int32_t _code_type;
      _code_type code;
      enum { UNKNOWN_ERROR =  1 };
      enum { DATABASE_NOT_CONNECTED =  2 };
      enum { DATABASE_QUERY_ERROR =  3 };
      enum { SUCCESS =  -1 };

    DatabaseReturnCode():
      code(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_code;
      u_code.real = this->code;
      *(outbuffer + offset + 0) = (u_code.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_code.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_code.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_code.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->code);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_code;
      u_code.base = 0;
      u_code.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_code.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_code.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_code.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->code = u_code.real;
      offset += sizeof(this->code);
     return offset;
    }

    virtual const char * getType() override { return "household_objects_database_msgs/DatabaseReturnCode"; };
    virtual const char * getMD5() override { return "b649fd6fa3a4e3bf8e3f4b4e648fa0f1"; };

  };

}
#endif
