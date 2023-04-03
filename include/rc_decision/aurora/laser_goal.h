/*
 * @Author: robox-xx 1399786770@qq.com
 * @Date: 2023-03-29 14:23:28
 * @LastEditors: robox-xx 1399786770@qq.com
 * @LastEditTime: 2023-04-03 14:21:56
 */
#pragma once
#ifndef MOVEBASE_BT_NODES_H
#define MOVEBASE_BT_NODES_H
#include <math.h>
#include<chrono>
#include <iostream>
#include <ros/ros.h>
#include <behaviortree_cpp_v3/action_node.h>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Float64MultiArray.h>


using namespace std;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

struct Pose2D
{
  double x, y, theta;
};

namespace rc_decision {

class laser_goal : public BT::StatefulActionNode {
 public:
  laser_goal(const std::string& name, const BT::NodeConfiguration& config) 
      : BT::StatefulActionNode(name, config), 
      ac("move_base", true)
    {
        ros::NodeHandle n;
        radar_org_data_ = n.subscribe("the_best_way", 5, &laser_goal::LaserCallback, this);
    };

  // Initialization of keys
  static BT::PortsList providedPorts() {
    BT::PortsList ports_list;   
    ports_list.insert(BT::InputPort<Pose2D>("Goal_point"));
    return ports_list;
  }

    BT::NodeStatus onStart() override;

    BT::NodeStatus onRunning() override;

    void onHalted() override;

  private:
    Pose2D goal_point_;
    MoveBaseClient ac_;
    bool _aborted;
    
    std_msgs::Float64MultiArray the_best_way_;
    ros::Subscriber radar_org_data_;
    chrono::system_clock::time_point _completion_time;
    void LaserCallback(const std_msgs::Float64MultiArray msg)
    {
      the_best_way_=msg;
    };
    
};

}
#endif   // laser_goal