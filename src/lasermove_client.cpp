/*
 * @Author: JIAlonglong
 * @Date: 2023-03-06 15:50:46
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-03-08 15:51:11
 * @FilePath: /rc_ws/src/rc_fsm/rc_decision/src/lasermove_client.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <rc_decision/aurora/lasermove_client.h>
#include <tf/transform_datatypes.h>
BT::NodeStatus rc_decision::lasermove::tick(){
if (!_client.waitForServer(ros::Duration(2.0))) {
    ROS_ERROR("Can't contact move_base server");
    return BT::NodeStatus::FAILURE;
  }
  _start=true;  
if (_received)
{
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
else
{
  return BT::NodeStatus::RUNNING;
}
}


void rc_decision::lasermove::Callback(const rc_msgs::GoalPointConstPtr &msg)
{
    if (!msg) {
      ROS_WARN("Received null pointer");
      return;
    }
    if (!msg->master) {
      _received = false;
      ROS_WARN("Please set master to true");
      return;
    }
    if (msg->goal.point.x == 0 && msg->goal.point.y == 0) {
      _received = false;
      ROS_WARN("Position information not received");
      return;
    }
    if (std::isnan(msg->goal.point.z)) {
      _received = false;
      ROS_WARN("Orientation information not received");
      return;
    }

    ROS_INFO("AUTO MODE! Sending goal %f %f %f", msg->goal.point.x, msg->goal.point.y, msg->goal.point.z);  
    _msg.target_pose.header.frame_id = "map";
    _msg.target_pose.header.stamp = ros::Time::now();
    _msg.target_pose.pose.position.x = msg->goal.point.x;
    _msg.target_pose.pose.position.y = msg->goal.point.y;
    tf::Quaternion rot = tf::createQuaternionFromYaw(msg->goal.point.z);
    tf::quaternionTFToMsg(rot, _msg.target_pose.pose.orientation);
    _client.sendGoal(_msg);
    _received = true;  
        
}