/*
 * @Author: JIAlonglong
 * @Date: 2023-01-15 20:19:40
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-01-19 17:16:09
 * @FilePath: /rc_ws/src/rc_fsm/rc_decision/src/move_base_client.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by JIAlonglong 2495477531@qq.com, All Rights Reserved. 
 */
#include <rc_decision/aurora/movebase_client.h>
//you can also write in tick function
BT::NodeStatus MoveBase::tick() {
  // if no server is present, fail after 2 seconds
  if (!_client.waitForServer(ros::Duration(2.0))) {
    ROS_ERROR("Can't contact move_base server");
    return BT::NodeStatus::FAILURE;
  }

  // Take the goal from the InputPort of the Node
  Pose2D goal;
  if (!getInput<Pose2D>("goal", goal)) {
    // if I can't get this, there is something wrong with your BT.
    // For this reason throw an exception instead of returning FAILURE
    throw BT::RuntimeError("missing required input [goal]");
  }

  // Reset this flag
  _aborted = false;

  ROS_INFO("Sending goal %f %f %f ", goal.x, goal.y, goal.theta);

  // Build the message from Pose2D
  move_base_msgs::MoveBaseGoal msg;
  msg.target_pose.header.frame_id = "map";
  msg.target_pose.header.stamp = ros::Time::now();
  msg.target_pose.pose.position.x = goal.x;
  msg.target_pose.pose.position.y = goal.y;
  tf::Quaternion rot = tf::createQuaternionFromYaw(goal.theta);
  tf::quaternionTFToMsg(rot, msg.target_pose.pose.orientation);

  _client.sendGoal(msg);

  while (!_aborted && !_client.waitForResult(ros::Duration(0.02))) {
    // polling at 50 Hz. No big deal in terms of CPU
  }

  if (_aborted) {
    // this happens only if method halt() was invoked
    //_client.cancelAllGoals();
    ROS_ERROR("MoveBase aborted");
    return BT::NodeStatus::FAILURE;
  }

  if (_client.getState() != actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_ERROR("MoveBase failed");
    return BT::NodeStatus::FAILURE;
  }

  ROS_INFO("Target reached");
  return BT::NodeStatus::SUCCESS;
}
