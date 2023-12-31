#ifndef _ROS_SERVICE_GetModelMesh_h
#define _ROS_SERVICE_GetModelMesh_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "shape_msgs/Mesh.h"
#include "household_objects_database_msgs/DatabaseReturnCode.h"

namespace household_objects_database_msgs
{

static const char GETMODELMESH[] = "household_objects_database_msgs/GetModelMesh";

  class GetModelMeshRequest : public ros::Msg
  {
    public:
      typedef int32_t _model_id_type;
      _model_id_type model_id;

    GetModelMeshRequest():
      model_id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_model_id;
      u_model_id.real = this->model_id;
      *(outbuffer + offset + 0) = (u_model_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_model_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_model_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_model_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->model_id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_model_id;
      u_model_id.base = 0;
      u_model_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_model_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_model_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_model_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->model_id = u_model_id.real;
      offset += sizeof(this->model_id);
     return offset;
    }

    virtual const char * getType() override { return GETMODELMESH; };
    virtual const char * getMD5() override { return "28cb0598daf3b969068a38cd07aaa9f6"; };

  };

  class GetModelMeshResponse : public ros::Msg
  {
    public:
      typedef household_objects_database_msgs::DatabaseReturnCode _return_code_type;
      _return_code_type return_code;
      typedef shape_msgs::Mesh _mesh_type;
      _mesh_type mesh;

    GetModelMeshResponse():
      return_code(),
      mesh()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->return_code.serialize(outbuffer + offset);
      offset += this->mesh.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->return_code.deserialize(inbuffer + offset);
      offset += this->mesh.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return GETMODELMESH; };
    virtual const char * getMD5() override { return "350330c487efb062c09ffe1ab80683de"; };

  };

  class GetModelMesh {
    public:
    typedef GetModelMeshRequest Request;
    typedef GetModelMeshResponse Response;
  };

}
#endif
