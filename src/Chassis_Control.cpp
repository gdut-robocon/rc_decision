/*
 * @Author: robox-xx 1399786770@qq.com
 * @Date: 2023-03-15 11:04:27
 * @LastEditors: robox-xx 118261752+robox-xx@users.noreply.github.com
 * @LastEditTime: 2023-04-18 15:47:46
 */
#include <ros/ros.h>
#include <iostream>
#include <rc_msgs/IbusData.h>
#include <rc_decision/aurora/Chassis_Control.h>


BT::NodeStatus rc_decision::Chassis_Control::tick()
{
    //拿出黑板数据
    auto IbusData = getInput<rc_msgs::IbusData>("Ibusdata");
    if(IbusData.value().sw_a==1){
      ROS_INFO("you are in the head model");
      vel.linear.x = 2*IbusData.value().ch_l_y;
      vel.linear.y = -IbusData.value().ch_l_x;
      vel.angular.z = -IbusData.value().ch_r_x;

      pub_cmdvel.publish(vel);
      return BT::NodeStatus::SUCCESS;
    }
    else if(IbusData.value().sw_a==2)
    {
      ROS_INFO("you are in the auto model");
      return BT::NodeStatus::FAILURE;
    }
    else
    {
      return BT::NodeStatus::SUCCESS;
    }
    
};
