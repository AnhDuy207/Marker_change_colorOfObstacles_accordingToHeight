#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE_LIST;   //CUBE

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
    int _N = 4;
    int resolution_ = 1.0;
    // float randColor = rand()%2;
    for (int x = 0; x < _N; x++) {
          for (int y = 0; y < _N; y++) {
              for (int z = 0; z < _N; z++) {
              
                  geometry_msgs::Point p;
                  p.x = x * resolution_;
                  p.y = y * resolution_;
                  p.z = z * resolution_;

                  std_msgs::ColorRGBA color;
                  if(z==0){
                    color.r = 1;
                    color.g = 1;
                    color.b = 0;
                    color.a = 1.0;
                  } else if(z==1){
                    color.r = (float)189/255;
                    color.g = (float)183/255;
                    color.b = (float)107/255;
                    color.a = 1.0;
                  } else if(z==2){
                    color.r = (float)240/255;
                    color.g = (float)230/255;
                    color.b = (float)140/255;
                    color.a = 1.0;
                  } else if(z==3){
                    color.r = (float)238/255;
                    color.g = (float)232/255;
                    color.b = (float)170/255;
                    color.a = 1.0;
                  }

                  marker.colors.push_back(color);
                  marker.points.push_back(p);
              }
          }
      }
    // Publish the marker
    // while (marker_pub.getNumSubscribers() < 1)
    // {
    //   if (!ros::ok())
    //   {
    //     return 0;
    //   }
    //   ROS_WARN_ONCE("Please create a subscriber to the marker");
    //   sleep(1);
    // }
    std::cout << "Hello" << std::endl; 
    marker_pub.publish(marker);

    // Cycle between different shapes
    // switch (shape)
    // {
    // case visualization_msgs::Marker::CUBE:
    //   shape = visualization_msgs::Marker::SPHERE;
    //   break;
    // case visualization_msgs::Marker::SPHERE:
    //   shape = visualization_msgs::Marker::ARROW;
    //   break;
    // case visualization_msgs::Marker::ARROW:
    //   shape = visualization_msgs::Marker::CYLINDER;
    //   break;
    // case visualization_msgs::Marker::CYLINDER:
    //   shape = visualization_msgs::Marker::CUBE;
    //   break;
    // }

    r.sleep();
  }
}
