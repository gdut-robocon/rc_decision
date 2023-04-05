/*
 * @Author: robox-xx 1399786770@qq.com
 * @Date: 2023-03-15 11:04:27
 * @LastEditors: robox-xx 1399786770@qq.com
 * @LastEditTime: 2023-04-03 14:19:33
 * @FilePath: /rc_ws/src/rc_decision/include/rc_decision/blackboard/blackboard.h
 */
#pragma once
#include <rc_decision/bt_action_node.h>
#include <rc_decision/bt_service_node.h>
#include <std_msgs/Float64MultiArray.h>

namespace rc_decision
{
class BlackboardRead : public BT::SyncActionNode
{
    public:
    BlackboardRead(const std::string& name, const BT::NodeConfiguration& config): BT::SyncActionNode(name, config)
    {
        ros::NodeHandle nh;
        radar_tf_data_ = nh.subscribe("/map/shootPosition", 5, &BlackboardRead::LadarCallback, this);
    };
    
    //Initialization of keys
    static BT::PortsList providedPorts() {
        BT::PortsList ports_list;   
        ports_list.insert(BT::OutputPort<Pose2D>("Goal"));
        return ports_list;
    }

    //Adding data to the blackboard
    BT::NodeStatus tick() override {
    
        setOutput("Goal", goal_);
        ROS_INFO("i send x:%f, y:%f", goal_.x,goal_.y);
        
        return BT::NodeStatus::SUCCESS;
    };



    private:
    
    ros::Subscriber radar_tf_data_;
    ros::Subscriber ibus_data_;
    Pose2D goal_;

    void LadarCallback(const std_msgs::Float64MultiArray msg)
   {
        goal_.x=msg.data[0];
        goal_.y=msg.data[1];  
        goal_.theta = atan(goal_.x/goal_.y);
   }
   
};
} //namespace rc_decision