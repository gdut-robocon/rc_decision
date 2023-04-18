/*
 * @Author: robox-xx 1399786770@qq.com
 * @Date: 2023-03-15 11:04:27
 * @LastEditors: robox-xx 118261752+robox-xx@users.noreply.github.com
 * @LastEditTime: 2023-04-18 15:47:04
 */
#include <ros/ros.h>
#include <rc_decision/aurora/Move_to_targe.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <tf/transform_datatypes.h>
BT::NodeStatus rc_decision::Move_to_targe::tick()
{
  if (!ac_.waitForServer(ros::Duration(2.0))) {
    ROS_ERROR("Can't contact move_base server");
    return BT::NodeStatus::FAILURE;
  }

  if ( !getInput<Pose2D>("Goal_point", goal_point))
  {
    throw BT::RuntimeError("missing required input [Goal_point]");
  }
  ROS_INFO("[ MoveBase: SEND REQUEST ]. goal: x=%f y=%f theta=%f\n",
         goal_point.x, goal_point.y, goal_point.theta);


if(goal_point.x!=0&&goal_point.y!=0&&std::isfinite(goal_point.x)&&std::isfinite(goal_point.y))
{
 // Build the message from Pose2D
  move_base_msgs::MoveBaseGoal msg;
  msg.target_pose.header.frame_id = "map";
  msg.target_pose.header.stamp = ros::Time::now();
  //后期通过筛选再选择要到达的点
  // msg.target_pose.pose.position.x = goal_point.x;
  // msg.target_pose.pose.position.y = goal_point.y;
  msg.target_pose.pose.position.x = 1;
  msg.target_pose.pose.position.y = 0;
  msg.target_pose.pose.orientation.z = 0;
  msg.target_pose.pose.orientation.w = 1;

  // We use this counter to simulate an action that takes a certain
  // amount of time to be completed (200 ms)
  ac_.sendGoal(msg);
  _aborted = false;
  

 while (ros::ok() && !ac_.waitForResult(ros::Duration(0.1))){}
 if (_aborted) {
    // this happens only if method halt() was invoked
    ROS_ERROR("MoveBase aborted");
    return BT::NodeStatus::FAILURE;
  }
  if (ac_.getState() != actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_ERROR("MoveBase failed");
    return BT::NodeStatus::FAILURE;
  }
  return BT::NodeStatus::SUCCESS;
}
else
{
  return BT::NodeStatus::SUCCESS;
} 
}
//被修饰节点调用后暂停导航
void rc_decision::Move_to_targe::halt()
{
  ac_.cancelAllGoals();
  vel.linear.x = 0.0;
  vel.linear.y = 0.0;
  vel.angular.z = 0.0;
  pub_stop.publish(vel);
}