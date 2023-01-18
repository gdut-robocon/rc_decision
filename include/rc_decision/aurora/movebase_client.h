/*
 * @Author: JIAlonglong
 * @Date: 2023-01-17 22:29:59
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-01-18 22:05:30
 * @FilePath: /rc_ws/src/rc_fsm/rc_decision/include/rc_decision/aurora/movebase_client.h
 * @Description: 
 * 
 * Copyright (c) 2023 by JIAlonglong 2495477531@qq.com, All Rights Reserved. 
 */
#pragma once
#include <move_base_msgs/MoveBaseAction.h>
#include <rc_decision/bt_service_node.h>
#include <rc_decision/bt_action_node.h>
#include <tf/transform_datatypes.h>

struct Pose2D
{
    double x, y , quaternion_z, quaternion_w;
};

namespace BT
{
template <> inline
Pose2D convertFromString(StringView key)
{
    // three real numbers separated by semicolons
    auto parts = BT::splitString(key, ';');
    if (parts.size() != 4)
    {
        throw BT::RuntimeError("invalid input)");
    }
    else
    {
        Pose2D output;
        output.x     = convertFromString<double>(parts[0]);
        output.y     = convertFromString<double>(parts[1]);
        output.quaternion_z = convertFromString<double>(parts[2]);
        output.quaternion_w = convertFromString<double>(parts[3]);
        return output;
    }
}
} // end namespace BT override
class MoveBase : public BT::RosActionNode <move_base_msgs::MoveBaseAction>
{
    public:
    //node config necessary!!!
    MoveBase( ros::NodeHandle& handle, const std::string& name, const BT::NodeConfiguration & conf):
    RosActionNode<move_base_msgs::MoveBaseAction>(handle, name, conf) {}

    //Input where you want to go
    static BT::PortsList providedPorts()
    {
        return{BT::InputPort<Pose2D>("goal")};
    }
    //you should be attention to the pure virtual functions
    bool sendGoal(GoalType& goal)override
    {
        if (!getInput<double>("goal",goal.target_pose.pose.position.x))
        {
            return false;
        }
        ROS_INFO("MoveBase: sending request");
        return true;
    }
    
    BT::NodeStatus onResult(const ResultType& res) override
    {
        ROS_INFO("MoveBase: received!");
        if (_aborted)
        {
            ROS_ERROR("MoveBase aborted");
            return BT::NodeStatus::FAILURE;
        }
        

    }

    virtual BT::NodeStatus tick() override;

    virtual void halt() override
    {
        _aborted = true;
    }

    

    private:
    bool _aborted;
};