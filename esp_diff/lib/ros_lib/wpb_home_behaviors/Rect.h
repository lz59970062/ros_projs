#ifndef _ROS_wpb_home_behaviors_Rect_h
#define _ROS_wpb_home_behaviors_Rect_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace wpb_home_behaviors
{

  class Rect : public ros::Msg
  {
    public:
      uint32_t name_length;
      typedef char* _name_type;
      _name_type st_name;
      _name_type * name;
      uint32_t top_length;
      typedef int32_t _top_type;
      _top_type st_top;
      _top_type * top;
      uint32_t bottom_length;
      typedef int32_t _bottom_type;
      _bottom_type st_bottom;
      _bottom_type * bottom;
      uint32_t left_length;
      typedef int32_t _left_type;
      _left_type st_left;
      _left_type * left;
      uint32_t right_length;
      typedef int32_t _right_type;
      _right_type st_right;
      _right_type * right;
      uint32_t probability_length;
      typedef float _probability_type;
      _probability_type st_probability;
      _probability_type * probability;

    Rect():
      name_length(0), st_name(), name(nullptr),
      top_length(0), st_top(), top(nullptr),
      bottom_length(0), st_bottom(), bottom(nullptr),
      left_length(0), st_left(), left(nullptr),
      right_length(0), st_right(), right(nullptr),
      probability_length(0), st_probability(), probability(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->name_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->name_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->name_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->name_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->name_length);
      for( uint32_t i = 0; i < name_length; i++){
      uint32_t length_namei = strlen(this->name[i]);
      varToArr(outbuffer + offset, length_namei);
      offset += 4;
      memcpy(outbuffer + offset, this->name[i], length_namei);
      offset += length_namei;
      }
      *(outbuffer + offset + 0) = (this->top_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->top_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->top_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->top_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->top_length);
      for( uint32_t i = 0; i < top_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_topi;
      u_topi.real = this->top[i];
      *(outbuffer + offset + 0) = (u_topi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_topi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_topi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_topi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->top[i]);
      }
      *(outbuffer + offset + 0) = (this->bottom_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bottom_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->bottom_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->bottom_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bottom_length);
      for( uint32_t i = 0; i < bottom_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_bottomi;
      u_bottomi.real = this->bottom[i];
      *(outbuffer + offset + 0) = (u_bottomi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_bottomi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_bottomi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_bottomi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bottom[i]);
      }
      *(outbuffer + offset + 0) = (this->left_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->left_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->left_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->left_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left_length);
      for( uint32_t i = 0; i < left_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_lefti;
      u_lefti.real = this->left[i];
      *(outbuffer + offset + 0) = (u_lefti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lefti.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lefti.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lefti.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left[i]);
      }
      *(outbuffer + offset + 0) = (this->right_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->right_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->right_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->right_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right_length);
      for( uint32_t i = 0; i < right_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_righti;
      u_righti.real = this->right[i];
      *(outbuffer + offset + 0) = (u_righti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_righti.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_righti.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_righti.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right[i]);
      }
      *(outbuffer + offset + 0) = (this->probability_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->probability_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->probability_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->probability_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->probability_length);
      for( uint32_t i = 0; i < probability_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->probability[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t name_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      name_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      name_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      name_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->name_length);
      if(name_lengthT > name_length)
        this->name = (char**)realloc(this->name, name_lengthT * sizeof(char*));
      name_length = name_lengthT;
      for( uint32_t i = 0; i < name_length; i++){
      uint32_t length_st_name;
      arrToVar(length_st_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_name-1]=0;
      this->st_name = (char *)(inbuffer + offset-1);
      offset += length_st_name;
        memcpy( &(this->name[i]), &(this->st_name), sizeof(char*));
      }
      uint32_t top_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      top_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      top_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      top_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->top_length);
      if(top_lengthT > top_length)
        this->top = (int32_t*)realloc(this->top, top_lengthT * sizeof(int32_t));
      top_length = top_lengthT;
      for( uint32_t i = 0; i < top_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_top;
      u_st_top.base = 0;
      u_st_top.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_top.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_top.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_top.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_top = u_st_top.real;
      offset += sizeof(this->st_top);
        memcpy( &(this->top[i]), &(this->st_top), sizeof(int32_t));
      }
      uint32_t bottom_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      bottom_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      bottom_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      bottom_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->bottom_length);
      if(bottom_lengthT > bottom_length)
        this->bottom = (int32_t*)realloc(this->bottom, bottom_lengthT * sizeof(int32_t));
      bottom_length = bottom_lengthT;
      for( uint32_t i = 0; i < bottom_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_bottom;
      u_st_bottom.base = 0;
      u_st_bottom.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_bottom.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_bottom.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_bottom.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_bottom = u_st_bottom.real;
      offset += sizeof(this->st_bottom);
        memcpy( &(this->bottom[i]), &(this->st_bottom), sizeof(int32_t));
      }
      uint32_t left_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      left_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      left_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      left_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->left_length);
      if(left_lengthT > left_length)
        this->left = (int32_t*)realloc(this->left, left_lengthT * sizeof(int32_t));
      left_length = left_lengthT;
      for( uint32_t i = 0; i < left_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_left;
      u_st_left.base = 0;
      u_st_left.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_left.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_left.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_left.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_left = u_st_left.real;
      offset += sizeof(this->st_left);
        memcpy( &(this->left[i]), &(this->st_left), sizeof(int32_t));
      }
      uint32_t right_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      right_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      right_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      right_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->right_length);
      if(right_lengthT > right_length)
        this->right = (int32_t*)realloc(this->right, right_lengthT * sizeof(int32_t));
      right_length = right_lengthT;
      for( uint32_t i = 0; i < right_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_right;
      u_st_right.base = 0;
      u_st_right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_right = u_st_right.real;
      offset += sizeof(this->st_right);
        memcpy( &(this->right[i]), &(this->st_right), sizeof(int32_t));
      }
      uint32_t probability_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      probability_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      probability_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      probability_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->probability_length);
      if(probability_lengthT > probability_length)
        this->probability = (float*)realloc(this->probability, probability_lengthT * sizeof(float));
      probability_length = probability_lengthT;
      for( uint32_t i = 0; i < probability_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_probability));
        memcpy( &(this->probability[i]), &(this->st_probability), sizeof(float));
      }
     return offset;
    }

    virtual const char * getType() override { return "wpb_home_behaviors/Rect"; };
    virtual const char * getMD5() override { return "f2e8cef4f7bbfddf42bb42bcc97ae935"; };

  };

}
#endif
