/*
 * @Author: JIAlonglong
 * @Date: 2023-01-17 22:29:59
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-03-08 13:36:46
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
#include <actionlib/client/simple_action_client.h>
#include <ros/ros.h>
struct Pose2D
{
  double x, y, theta;
};

namespace BT
{
template <>
inline Pose2D convertFromString(StringView key)
{
  // three real numbers separated by semicolons
  auto parts = BT::splitString(key, ';');
  if (parts.size() != 3)
  {
    throw BT::RuntimeError("invalid input)");
  }
  else
  {
    Pose2D output;
    output.x = convertFromString<double>(parts[0]);
    output.y = convertFromString<double>(parts[1]);
    output.theta = convertFromString<double>(parts[2]);
    return output;
  }
}
}  // namespace BT
namespace rc_decision
{
class MoveBase : public BT::AsyncActionNode
{
public:
  MoveBase(const std::string& name, const BT::NodeConfiguration& config)
    : BT::AsyncActionNode(name, config), _client("move_base", true)
  {
  }

  // It is mandatory to define this static method.
  static BT::PortsList providedPorts()
  {
    return { BT::InputPort<Pose2D>("goal") };
  }

  virtual BT::NodeStatus tick() override;

  virtual void halt() override
  {
    _aborted = true;
  }

private:
  typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
  MoveBaseClient _client;
  bool _aborted;
};
}  // namespace rc_decision
