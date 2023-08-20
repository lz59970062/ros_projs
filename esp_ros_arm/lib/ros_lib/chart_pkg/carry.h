#ifndef _ROS_chart_pkg_carry_h
#define _ROS_chart_pkg_carry_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace chart_pkg
{

  class carry : public ros::Msg
  {
    public:
      typedef const char* _data_type;
      _data_type data;
      typedef int64_t _level_type;
      _level_type level;
      typedef int64_t _exp_type;
      _exp_type exp;

    carry():
      data(""),
      level(0),
      exp(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_data = strlen(this->data);
      varToArr(outbuffer + offset, length_data);
      offset += 4;
      memcpy(outbuffer + offset, this->data, length_data);
      offset += length_data;
      union {
        int64_t real;
        uint64_t base;
      } u_level;
      u_level.real = this->level;
      *(outbuffer + offset + 0) = (u_level.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_level.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_level.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_level.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_level.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_level.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_level.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_level.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->level);
      union {
        int64_t real;
        uint64_t base;
      } u_exp;
      u_exp.real = this->exp;
      *(outbuffer + offset + 0) = (u_exp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_exp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_exp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_exp.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_exp.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_exp.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_exp.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_exp.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->exp);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_data;
      arrToVar(length_data, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_data; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_data-1]=0;
      this->data = (char *)(inbuffer + offset-1);
      offset += length_data;
      union {
        int64_t real;
        uint64_t base;
      } u_level;
      u_level.base = 0;
      u_level.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_level.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_level.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_level.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_level.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_level.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_level.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_level.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->level = u_level.real;
      offset += sizeof(this->level);
      union {
        int64_t real;
        uint64_t base;
      } u_exp;
      u_exp.base = 0;
      u_exp.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_exp.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_exp.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_exp.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_exp.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_exp.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_exp.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_exp.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->exp = u_exp.real;
      offset += sizeof(this->exp);
     return offset;
    }

    virtual const char * getType() override { return "chart_pkg/carry"; };
    virtual const char * getMD5() override { return "36e3792c0f2d7624e87605d443b94c89"; };

  };

}
#endif
