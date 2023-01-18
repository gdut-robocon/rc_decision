/*
 * @Author: JIAlonglong
 * @Date: 2023-01-15 20:19:40
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-01-18 21:11:15
 * @FilePath: /rc_ws/src/rc_fsm/rc_decision/src/move_base_client.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by JIAlonglong 2495477531@qq.com, All Rights Reserved. 
 */
#include <rc_decision/aurora/movebase_client.h>
//you can also write in tick function
BT::NodeStatus MoveBase::tick()
{
    // no server is present , wait for 2 seconds
    if (!MoveBase::action_client_->waitForServer(ros::Duration(2.0)))
    {
        ROS_ERROR("Can't contact move_base server");
        return BT::NodeStatus::FAILURE;
    }
    //Take the goal from xml
    Pose2D goal;
    if (!getInput<Pose2D>("goal" , goal))
    {
        //if I can not get this, there is something wrong with your BT.
        //For this reason throw an exception instead of returning FAILURE 
        throw BT::RuntimeError("missing required input [goal]");
    }

    //Reset this flag
    _aborted = false;

    ROS_INFO("Sending goal %f %f %f %f", goal.x, goal.y, goal.quaternion_z, goal.quaternion_w);

    //Build the message from Pose2D
    move_base_msgs::MoveBaseGoal msg;
    msg.target_pose.header.frame_id = "map";
    msg.target_pose.header.stamp = ros::Time::now();
    msg.target_pose.pose.position.x = goal.x;
    msg.target_pose.pose.orientation.z = goal.quaternion_z;
    msg.target_pose.pose.orientation.w = goal.quaternion_w;

    MoveBase::action_client_->sendGoal(msg);

    while (!_aborted && !MoveBase::action_client_->waitForResult(ros::Duration(0.02)))
    {
        //polling at 50HZ. No big deal in terms of CPU
    }

    if (_aborted)
    {
        //this happens only if method halt() was invoked
        //MoveBase::action_client_->cancelAllGoals();
        ROS_ERROR("MoveBase aborted");
        return BT::NodeStatus::FAILURE;
    }

    if (MoveBase::action_client_->getState()!= actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_ERROR("MoveBase failed");
        return BT::NodeStatus::FAILURE;
    }

    ROS_INFO("Target reached");
    return BT::NodeStatus::SUCCESS;
}