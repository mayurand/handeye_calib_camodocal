#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <sstream>

/**
 * This code converts PoseStamped msgs to tf:transformed msg in ROS
 */
tf::TransformBroadcaster * br;

void chatterCallback(const geometry_msgs::PoseStamped& msg)
{
  tf::StampedTransform bt;

  bt.setData(tf::Transform(tf::Quaternion(msg.pose.orientation.x,
                            msg.pose.orientation.y,
                            msg.pose.orientation.z,
                            msg.pose.orientation.w),
                 tf::Vector3(msg.pose.position.x, msg.pose.position.y, msg.pose.position.z)));
  bt.stamp_ = ros::Time::now();
  bt.frame_id_ = msg.header.frame_id;
  bt.child_frame_id_ = "iiwa_eef";
  br->sendTransform(bt);

}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
   ros::init(argc,argv,"beginner_tutorials");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  br = new tf::TransformBroadcaster();
  ros::Subscriber listen_poses = n.subscribe("/iiwa/state/CartesianPose", 100, chatterCallback);


  //ros::Publisher pub_tf_rob = n.advertise<tf::StampedTransform>("pub_tf_robot", 10);

  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {

    // ROS_INFO("START");

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
