#ifndef _ROS_manipulation_msgs_ClusterBoundingBox_h
#define _ROS_manipulation_msgs_ClusterBoundingBox_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Vector3.h"

namespace manipulation_msgs
{

  class ClusterBoundingBox : public ros::Msg
  {
    public:
      typedef geometry_msgs::PoseStamped _pose_stamped_type;
      _pose_stamped_type pose_stamped;
      typedef geometry_msgs::Vector3 _dimensions_type;
      _dimensions_type dimensions;

    ClusterBoundingBox():
      pose_stamped(),
      dimensions()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->pose_stamped.serialize(outbuffer + offset);
      offset += this->dimensions.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->pose_stamped.deserialize(inbuffer + offset);
      offset += this->dimensions.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "manipulation_msgs/ClusterBoundingBox"; };
    virtual const char * getMD5() override { return "9bf2b7a44ad666dc3a6a2bbc21782dad"; };

  };

}
#endif
