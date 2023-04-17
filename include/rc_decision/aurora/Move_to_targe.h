/*
 * @Author: robox-xx 1399786770@qq.com
 * @Date: 2023-03-29 14:23:28
 * @LastEditors: robox-xx 1399786770@qq.com
 * @LastEditTime: 2023-04-03 14:21:56
 * @FilePath: /rc_ws/src/rc_decision/include/rc_decision/aurora/laser_goal.h
 */

#pragma once
#include <math.h>
#include<chrono>
#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <behaviortree_cpp_v3/action_node.h>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Float64MultiArray.h>
#include <rc_decision/aurora/movebase_client.h>

namespace rc_decision {

class Move_to_targe : public BT::AsyncActionNode {
 public:
  Move_to_targe(const std::string& name, const BT::NodeConfiguration& config) 
      : BT::AsyncActionNode(name, config), 
      ac_("move_base", true)
    {
        ros::NodeHandle n;
        pub_stop = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    };

  // Initialization of keys
  static BT::PortsList providedPorts() {
    BT::PortsList ports_list;   
    ports_list.insert(BT::InputPort<Pose2D>("Goal_point"));
    return ports_list;
  }

    BT::NodeStatus tick() override;
    void halt() override;


  private:
    Pose2D goal_point;
    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
    MoveBaseClient ac_;
    bool _aborted;
  
    ros::Subscriber radar_org_data;
    std::chrono::system_clock::time_point _completion_time;

    ros::Publisher pub_stop;
    geometry_msgs::Twist vel;
    
};

}
// laser_goal