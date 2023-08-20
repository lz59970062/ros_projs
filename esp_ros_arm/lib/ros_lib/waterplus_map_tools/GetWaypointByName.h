#ifndef _ROS_SERVICE_GetWaypointByName_h
#define _ROS_SERVICE_GetWaypointByName_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace waterplus_map_tools
{

static const char GETWAYPOINTBYNAME[] = "waterplus_map_tools/GetWaypointByName";

  class GetWaypointByNameRequest : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;

    GetWaypointByNameRequest():
      name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    virtual const char * getType() override { return GETWAYPOINTBYNAME; };
    virtual const char * getMD5() override { return "c1f3d28f1b044c871e6eff2e9fc3c667"; };

  };

  class GetWaypointByNameResponse : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;

    GetWaypointByNameResponse():
      name(""),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return GETWAYPOINTBYNAME; };
    virtual const char * getMD5() override { return "177d54286ddeee12eba514054bddffd5"; };

  };

  class GetWaypointByName {
    public:
    typedef GetWaypointByNameRequest Request;
    typedef GetWaypointByNameResponse Response;
  };

}
#endif
