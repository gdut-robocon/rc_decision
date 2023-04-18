/*
 * @Author: robox-xx 1399786770@qq.com
 * @Date: 2023-03-15 11:04:27
 * @LastEditors: robox-xx 1399786770@qq.com
 * @LastEditTime: 2023-04-17 14:19:33
 */
#pragma once
#include <ros/ros.h>
#include <iostream>
#include <move_base_msgs/MoveBaseAction.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Twist.h>
#include <rc_msgs/IbusData.h>
#include <std_msgs/Float64MultiArray.h>


namespace rc_decision {

class Chassis_Control : public BT::SyncActionNode {
 public:
  Chassis_Control (const std::string& name, const BT::NodeConfiguration& config) : BT::SyncActionNode(name, config)
  {
    pub_cmdvel = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  };

  // 这个必须要写，处理接口参数的
  static BT::PortsList providedPorts() {
    BT::PortsList ports_list; 
    //拿出黑板数据的初始化
    ports_list.insert(BT::InputPort<rc_msgs::IbusData>("Ibusdata"));
    return ports_list;
  }

  BT::NodeStatus tick() override;

  private:
    ros::NodeHandle nh;
    ros::Publisher pub_cmdvel;
    geometry_msgs::Twist vel;
};

}
