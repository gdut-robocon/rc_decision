//
// Created by jialonglong on 23-4-7.
//

#pragma once
#include <rc_decision/bt_action_node.h>
#include <rc_decision/bt_service_node.h>
#include <geometry_msgs/Twist.h>
namespace rc_decision
{
class ChassisMove : public BT::StatefulActionNode
{
public:
  ChassisMove(const std::string& name, const BT::NodeConfiguration& config) : BT::StatefulActionNode(name, config){};
  static BT::PortsList providedPorts()
  {
    return { BT::InputPort<float>("Joy_LX"), BT::InputPort<float>("Joy_LY"), BT::InputPort<float>("Joy_RX"),
             BT::InputPort<float>("Joy_RY") };
  }
  BT::NodeStatus onStart() override;

  BT::NodeStatus onRunning() override;

  void onHalted() override;
private:
  ros::Publisher cmd_vel_pub_;
  geometry_msgs::Twist cmd_vel_;
  float joy_lx_, joy_ly_, joy_rx_, joy_ry_;
  double linear_x_scale_, linear_y_scale_, angular_z_scale_;
  bool _aborted;
};

}//namespace rc_decision
