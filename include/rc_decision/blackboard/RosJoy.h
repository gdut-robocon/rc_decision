//
// Created by jialonglong on 23-4-7.
//

#pragma once
#include <rc_decision/bt_action_node.h>
#include <rc_decision/bt_service_node.h>
#include <sensor_msgs/Joy.h>
namespace rc_decision
{
class RosJoy : public BT::SyncActionNode
{
public:
  RosJoy(const std::string& name, const BT::NodeConfiguration& config) : BT::SyncActionNode(name, config){};

  static BT::PortsList providedPorts()
  {
    BT::PortsList ports;
    ports.insert(BT::OutputPort<float>("Joy_LX"));
    ports.insert(BT::OutputPort<float>("Joy_LY"));
    ports.insert(BT::OutputPort<float>("Joy_RY"));
    return ports;
  }

  BT::NodeStatus tick() override
  {
    ros::NodeHandle n("~");
    ros::NodeHandle controller_nh;
    joy_sub_ = controller_nh.subscribe("joy", 10, &RosJoy::joyCallback, this);
    n.getParam("axes_lx", linear_x);
    n.getParam("axes_ly", linear_y);
    n.getParam("axes_angular", angular_);
    if (joy_received_)
    {
      setOutput("Joy_LX", joy_lx_);
      setOutput("Joy_LY", joy_ly_);
      setOutput("Joy_RY", joy_ry_);
      ROS_INFO("Joy_LX: %f, Joy_LY: %f, Joy_RY: %f", joy_lx_, joy_ly_, joy_ry_);
      return BT::NodeStatus::SUCCESS;
    } 
    else
    {
      return BT::NodeStatus::FAILURE;
    }
  }

private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
    {
        joy_received_= true;
        joy_lx_=joy->axes[linear_x];
        joy_ly_ = joy->axes[linear_y];
        joy_ry_=joy->axes[angular_];
    }
    ros::Subscriber joy_sub_;
    bool joy_received_;
    float joy_lx_,joy_ly_,joy_rx_,joy_ry_;
    int A_button_,B_button_,X_button_,Y_button_,LB_button_,RB_button_,L_THUMB_button_,R_THUMB_button_,BACK_button_,START_button_;
    int linear_x,linear_y,angular_;
};
}//namespace rc_decision
