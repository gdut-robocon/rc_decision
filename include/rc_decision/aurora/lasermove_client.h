/*
 * @Author: JIAlonglong
 * @Date: 2023-03-06 15:30:59
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-03-08 14:05:30
 * @FilePath: /rc_ws/src/rc_fsm/rc_decision/include/rc_decision/aurora/lasermove_client.h
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#pragma once
#include <rc_msgs/GoalPoint.h>
#include <rc_decision/bt_action_node.h>
#include <rc_decision/bt_service_node.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <ros/ros.h>

namespace rc_decision
{
    class lasermove : public BT::AsyncActionNode
    {
    private:
        ros::Subscriber lasermove_sub_;
        move_base_msgs::MoveBaseGoal _msg;
        bool _aborted;
        bool _received;
        bool _start;
        typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
        MoveBaseClient _client;
    public:
        lasermove(const std::string& name,const BT::NodeConfiguration& config,const ros::NodeHandle& root_nh,
                        const ros::NodeHandle& tree_nh): BT::AsyncActionNode(name,config),
                        _client("lasermove", true),
                        _received(false),
                        _aborted(false),
                        _start(false){
                            ros::NodeHandle nh(root_nh);
                            if(_start)
                            {lasermove_sub_=nh.subscribe<rc_msgs::GoalPoint>("goal_target",1,&lasermove::Callback,this);}
                        };          

        static BT::PortsList providedPorts() {
        BT::PortsList ports_list;
        return ports_list;
        }

       virtual void halt() override
        {
        _aborted = true;
        }   

        virtual BT::NodeStatus tick() override;

        void Callback(const rc_msgs::GoalPointConstPtr &msg);

    };
    
} // namespace rc_decision

