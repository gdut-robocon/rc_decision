/*
 * @Author: JIAlonglong
 * @Date: 2023-01-17 22:20:38
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-03-06 17:14:57
 * @FilePath: /rc_ws/src/rc_fsm/rc_decision/include/rc_decision/blackboard/blackboard.h
 * @Description: blackboard is a node help others' nodes to communicate with rc_msgs
 * 
 * Copyright (c) 2023 by JIAlonglong 2495477531@qq.com, All Rights Reserved. 
 */
#pragma once
#include <rc_msgs/ActionData.h>
#include <rc_msgs/ActuatorState.h>
#include <rc_msgs/ChassisCmd.h>
#include <rc_msgs/GimbalCmd.h>
#include <rc_msgs/GimbalDesError.h>
#include <rc_msgs/LpData.h>
#include <rc_msgs/IbusData.h>
#include <rc_msgs/GoalPoint.h>
#include <rc_decision/bt_action_node.h>
#include <rc_decision/bt_service_node.h>
namespace rc_decision
{
class BlackboardRead : public BT::AsyncActionNode
{
    public:
    BlackboardRead(const std::string& name, const BT::NodeConfiguration& config, const ros::NodeHandle& root_nh,
        const ros::NodeHandle& nh)
    {

    };

    private:

};
} //namespace rc_decision