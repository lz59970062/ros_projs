#ifndef _ROS_SERVICE_Follow_h
#define _ROS_SERVICE_Follow_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace wpb_home_tutorials
{

static const char FOLLOW[] = "wpb_home_tutorials/Follow";

  class FollowRequest : public ros::Msg
  {
    public:
      typedef float _thredhold_type;
      _thredhold_type thredhold;

    FollowRequest():
      thredhold(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_thredhold;
      u_thredhold.real = this->thredhold;
      *(outbuffer + offset + 0) = (u_thredhold.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thredhold.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thredhold.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thredhold.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thredhold);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_thredhold;
      u_thredhold.base = 0;
      u_thredhold.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thredhold.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thredhold.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thredhold.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thredhold = u_thredhold.real;
      offset += sizeof(this->thredhold);
     return offset;
    }

    virtual const char * getType() override { return FOLLOW; };
    virtual const char * getMD5() override { return "c112d3700d2186140dee3c92caad02d8"; };

  };

  class FollowResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    FollowResponse():
      result(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
     return offset;
    }

    virtual const char * getType() override { return FOLLOW; };
    virtual const char * getMD5() override { return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class Follow {
    public:
    typedef FollowRequest Request;
    typedef FollowResponse Response;
  };

}
#endif
