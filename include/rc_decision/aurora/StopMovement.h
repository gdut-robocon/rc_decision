/*
 * @Author: robox-xx 1399786770@qq.com
 * @Date: 2023-03-15 11:04:27
 * @LastEditors: robox-xx 118261752+robox-xx@users.noreply.github.com
 * @LastEditTime: 2023-04-18 15:46:03
 */
#pragma once
#include <ros/ros.h>
#include <iostream>
#include <rc_msgs/IbusData.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <behaviortree_cpp_v3/behavior_tree.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <rc_decision/aurora/Move_to_targe.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
//利用该自定义修饰节点暂停导航
namespace rc_decision {

class StopMovement : public BT::DecoratorNode {
 public:
  StopMovement (const std::string& name, const BT::NodeConfiguration& config)
   : BT::DecoratorNode(name, config)
  {
    ros::NodeHandle n;
    ibus_data_ = n.subscribe("ibus_data", 5, &StopMovement::IbusCallback, this);
  };

  // 这个必须要写，处理接口参数的
  static BT::PortsList providedPorts() {
    BT::PortsList ports_list; 
    //拿出黑板数据的初始化
    return ports_list;
  }

  BT::NodeStatus tick() override
  {
    // 获取子节点并执行
    auto child_node = child();
    const auto child_status = child()->executeTick();
        

    // 如果子节点返回FAILURE，则立即中断
    if (child_status == BT::NodeStatus::FAILURE)
    {
        child()->halt();
        return BT::NodeStatus::FAILURE;
    }
    if (child_status == BT::NodeStatus::RUNNING)
    {
      if(ibus_.sw_d == 2)
      {
        child()->halt();
        return BT::NodeStatus::FAILURE;
      }
    }

      return BT::NodeStatus::SUCCESS;

    }
  private:
  ros::Subscriber ibus_data_;
  rc_msgs::IbusData ibus_;
  void IbusCallback(const rc_msgs::IbusDataConstPtr& ibus_data)
  {
        ibus_.sw_d = ibus_data->sw_d;
  }

};

}
