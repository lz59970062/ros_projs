#ifndef _ROS_wpb_home_behaviors_Coord_h
#define _ROS_wpb_home_behaviors_Coord_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace wpb_home_behaviors
{

  class Coord : public ros::Msg
  {
    public:
      uint32_t name_length;
      typedef char* _name_type;
      _name_type st_name;
      _name_type * name;
      uint32_t x_length;
      typedef float _x_type;
      _x_type st_x;
      _x_type * x;
      uint32_t y_length;
      typedef float _y_type;
      _y_type st_y;
      _y_type * y;
      uint32_t z_length;
      typedef float _z_type;
      _z_type st_z;
      _z_type * z;
      uint32_t probability_length;
      typedef float _probability_type;
      _probability_type st_probability;
      _probability_type * probability;

    Coord():
      name_length(0), st_name(), name(nullptr),
      x_length(0), st_x(), x(nullptr),
      y_length(0), st_y(), y(nullptr),
      z_length(0), st_z(), z(nullptr),
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
      *(outbuffer + offset + 0) = (this->x_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->x_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->x_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->x_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x_length);
      for( uint32_t i = 0; i < x_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->x[i]);
      }
      *(outbuffer + offset + 0) = (this->y_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->y_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->y_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_length);
      for( uint32_t i = 0; i < y_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->y[i]);
      }
      *(outbuffer + offset + 0) = (this->z_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->z_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->z_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->z_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->z_length);
      for( uint32_t i = 0; i < z_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->z[i]);
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
      uint32_t x_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      x_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      x_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      x_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->x_length);
      if(x_lengthT > x_length)
        this->x = (float*)realloc(this->x, x_lengthT * sizeof(float));
      x_length = x_lengthT;
      for( uint32_t i = 0; i < x_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_x));
        memcpy( &(this->x[i]), &(this->st_x), sizeof(float));
      }
      uint32_t y_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      y_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      y_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      y_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->y_length);
      if(y_lengthT > y_length)
        this->y = (float*)realloc(this->y, y_lengthT * sizeof(float));
      y_length = y_lengthT;
      for( uint32_t i = 0; i < y_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_y));
        memcpy( &(this->y[i]), &(this->st_y), sizeof(float));
      }
      uint32_t z_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      z_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      z_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      z_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->z_length);
      if(z_lengthT > z_length)
        this->z = (float*)realloc(this->z, z_lengthT * sizeof(float));
      z_length = z_lengthT;
      for( uint32_t i = 0; i < z_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_z));
        memcpy( &(this->z[i]), &(this->st_z), sizeof(float));
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

    virtual const char * getType() override { return "wpb_home_behaviors/Coord"; };
    virtual const char * getMD5() override { return "f4c6bf06051abcb9913c14ef2b4e56f0"; };

  };

}
#endif
