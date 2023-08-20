#ifndef _ROS_SERVICE_GetNumOfWaypoints_h
#define _ROS_SERVICE_GetNumOfWaypoints_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace waterplus_map_tools
{

static const char GETNUMOFWAYPOINTS[] = "waterplus_map_tools/GetNumOfWaypoints";

  class GetNumOfWaypointsRequest : public ros::Msg
  {
    public:

    GetNumOfWaypointsRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
     return offset;
    }

    virtual const char * getType() override { return GETNUMOFWAYPOINTS; };
    virtual const char * getMD5() override { return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetNumOfWaypointsResponse : public ros::Msg
  {
    public:
      typedef int32_t _num_type;
      _num_type num;

    GetNumOfWaypointsResponse():
      num(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_num;
      u_num.real = this->num;
      *(outbuffer + offset + 0) = (u_num.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_num.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_num.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_num.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->num);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_num;
      u_num.base = 0;
      u_num.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_num.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_num.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_num.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->num = u_num.real;
      offset += sizeof(this->num);
     return offset;
    }

    virtual const char * getType() override { return GETNUMOFWAYPOINTS; };
    virtual const char * getMD5() override { return "54b3c80efd6fae6e6ffff8a4b9facd69"; };

  };

  class GetNumOfWaypoints {
    public:
    typedef GetNumOfWaypointsRequest Request;
    typedef GetNumOfWaypointsResponse Response;
  };

}
#endif
