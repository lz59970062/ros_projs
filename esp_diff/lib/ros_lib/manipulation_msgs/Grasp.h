#ifndef _ROS_manipulation_msgs_Grasp_h
#define _ROS_manipulation_msgs_Grasp_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/JointState.h"
#include "geometry_msgs/PoseStamped.h"
#include "manipulation_msgs/GripperTranslation.h"

namespace manipulation_msgs
{

  class Grasp : public ros::Msg
  {
    public:
      typedef const char* _id_type;
      _id_type id;
      typedef sensor_msgs::JointState _pre_grasp_posture_type;
      _pre_grasp_posture_type pre_grasp_posture;
      typedef sensor_msgs::JointState _grasp_posture_type;
      _grasp_posture_type grasp_posture;
      typedef geometry_msgs::PoseStamped _grasp_pose_type;
      _grasp_pose_type grasp_pose;
      typedef float _grasp_quality_type;
      _grasp_quality_type grasp_quality;
      typedef manipulation_msgs::GripperTranslation _approach_type;
      _approach_type approach;
      typedef manipulation_msgs::GripperTranslation _retreat_type;
      _retreat_type retreat;
      typedef float _max_contact_force_type;
      _max_contact_force_type max_contact_force;
      uint32_t allowed_touch_objects_length;
      typedef char* _allowed_touch_objects_type;
      _allowed_touch_objects_type st_allowed_touch_objects;
      _allowed_touch_objects_type * allowed_touch_objects;

    Grasp():
      id(""),
      pre_grasp_posture(),
      grasp_posture(),
      grasp_pose(),
      grasp_quality(0),
      approach(),
      retreat(),
      max_contact_force(0),
      allowed_touch_objects_length(0), st_allowed_touch_objects(), allowed_touch_objects(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_id = strlen(this->id);
      varToArr(outbuffer + offset, length_id);
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      offset += this->pre_grasp_posture.serialize(outbuffer + offset);
      offset += this->grasp_posture.serialize(outbuffer + offset);
      offset += this->grasp_pose.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->grasp_quality);
      offset += this->approach.serialize(outbuffer + offset);
      offset += this->retreat.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_max_contact_force;
      u_max_contact_force.real = this->max_contact_force;
      *(outbuffer + offset + 0) = (u_max_contact_force.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max_contact_force.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max_contact_force.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max_contact_force.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->max_contact_force);
      *(outbuffer + offset + 0) = (this->allowed_touch_objects_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->allowed_touch_objects_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->allowed_touch_objects_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->allowed_touch_objects_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->allowed_touch_objects_length);
      for( uint32_t i = 0; i < allowed_touch_objects_length; i++){
      uint32_t length_allowed_touch_objectsi = strlen(this->allowed_touch_objects[i]);
      varToArr(outbuffer + offset, length_allowed_touch_objectsi);
      offset += 4;
      memcpy(outbuffer + offset, this->allowed_touch_objects[i], length_allowed_touch_objectsi);
      offset += length_allowed_touch_objectsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_id;
      arrToVar(length_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_id-1]=0;
      this->id = (char *)(inbuffer + offset-1);
      offset += length_id;
      offset += this->pre_grasp_posture.deserialize(inbuffer + offset);
      offset += this->grasp_posture.deserialize(inbuffer + offset);
      offset += this->grasp_pose.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->grasp_quality));
      offset += this->approach.deserialize(inbuffer + offset);
      offset += this->retreat.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_max_contact_force;
      u_max_contact_force.base = 0;
      u_max_contact_force.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max_contact_force.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max_contact_force.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max_contact_force.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->max_contact_force = u_max_contact_force.real;
      offset += sizeof(this->max_contact_force);
      uint32_t allowed_touch_objects_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      allowed_touch_objects_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      allowed_touch_objects_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      allowed_touch_objects_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->allowed_touch_objects_length);
      if(allowed_touch_objects_lengthT > allowed_touch_objects_length)
        this->allowed_touch_objects = (char**)realloc(this->allowed_touch_objects, allowed_touch_objects_lengthT * sizeof(char*));
      allowed_touch_objects_length = allowed_touch_objects_lengthT;
      for( uint32_t i = 0; i < allowed_touch_objects_length; i++){
      uint32_t length_st_allowed_touch_objects;
      arrToVar(length_st_allowed_touch_objects, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_allowed_touch_objects; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_allowed_touch_objects-1]=0;
      this->st_allowed_touch_objects = (char *)(inbuffer + offset-1);
      offset += length_st_allowed_touch_objects;
        memcpy( &(this->allowed_touch_objects[i]), &(this->st_allowed_touch_objects), sizeof(char*));
      }
     return offset;
    }

    virtual const char * getType() override { return "manipulation_msgs/Grasp"; };
    virtual const char * getMD5() override { return "83bd11da422ea1917259ee456c0e315a"; };

  };

}
#endif
