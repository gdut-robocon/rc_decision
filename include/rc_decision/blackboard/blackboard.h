/*
 * @Author: robox-xx 1399786770@qq.com
 * @Date: 2023-03-15 11:04:27
 * @LastEditors: robox-xx 118261752+robox-xx@users.noreply.github.com
 * @LastEditTime: 2023-04-17 22:29:22
 * @FilePath: /rc_ws/src/rc_decision/include/rc_decision/blackboard/blackboard.h
 */
#pragma once
#include <rc_decision/bt_action_node.h>
#include <rc_decision/bt_service_node.h>
#include <std_msgs/Float64MultiArray.h>
#include <rc_msgs/IbusData.h>
#include <rc_decision/aurora/movebase_client.h>

namespace rc_decision
{
class BlackboardRead : public BT::SyncActionNode
{
    public:
    BlackboardRead(const std::string& name, const BT::NodeConfiguration& config): BT::SyncActionNode(name, config)
    {
        ros::NodeHandle nh;
        radar_tf_data_ = nh.subscribe("/radar/post_Position", 5, &BlackboardRead::LadarCallback, this);
        post_data_ = nh.subscribe("/base_link/post_Position", 5, &BlackboardRead::PostCallback, this);
        ibus_data_ = nh.subscribe("ibus_data", 5, &BlackboardRead::IbusCallback, this);
    };
    
    //Initialization of keys
    static BT::PortsList providedPorts() {
        BT::PortsList ports_list;   
        ports_list.insert(BT::OutputPort<Pose2D>("Goal"));

        ports_list.insert(BT::OutputPort<Pose2D>("sxy1"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy2"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy3"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy4"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy5"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy6"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy7"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy8"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy9"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy10"));
        ports_list.insert(BT::OutputPort<Pose2D>("sxy11"));

        ports_list.insert(BT::OutputPort<rc_msgs::IbusData>("Ibus_data"));

        return ports_list;
    }

    //Adding data to the blackboard
    BT::NodeStatus tick() override {
    
        setOutput("Goal", goal_);
        // ROS_INFO("i send x:%f, y:%f", goal_.x,goal_.y);
        
        setOutput("sxy1", sxy1);
        setOutput("sxy2", sxy2);
        setOutput("sxy3", sxy3);
        setOutput("sxy4", sxy4);
        setOutput("sxy5", sxy5);
        setOutput("sxy6", sxy6);
        setOutput("sxy7", sxy7);
        setOutput("sxy8", sxy8);
        setOutput("sxy9", sxy9);
        setOutput("sxy10", sxy10);
        setOutput("sxy11", sxy11);

        setOutput("Ibus_data", ibus_);
        ROS_INFO("ibus swa:%d,lx:%lf,ly:%lf,rx:%lf", ibus_.sw_a,ibus_.ch_l_x,ibus_.ch_l_y,ibus_.ch_r_x);
        return BT::NodeStatus::SUCCESS;
    };



    private:
    
    ros::Subscriber radar_tf_data_;
    ros::Subscriber ibus_data_;
    ros::Subscriber post_data_;

    Pose2D goal_;
    Pose2D sxy1;
    Pose2D sxy2;
    Pose2D sxy3;
    Pose2D sxy4;
    Pose2D sxy5;
    Pose2D sxy6;
    Pose2D sxy7;
    Pose2D sxy8;
    Pose2D sxy9;
    Pose2D sxy10;
    Pose2D sxy11;
    rc_msgs::IbusData ibus_;
    void LadarCallback(const std_msgs::Float64MultiArray msg)
    {
        goal_.x=msg.data[0];
        goal_.y=msg.data[1];  
        goal_.theta = atan(goal_.x/goal_.y);
    }
 
    void PostCallback(const std_msgs::Float64MultiArray post_data)
    {
        sxy1.x = post_data.data[0];
        sxy1.y = post_data.data[1];
        sxy1.theta = atan(sxy1.x/sxy1.y);

        sxy2.x = post_data.data[2];
        sxy2.y = post_data.data[3];
        sxy2.theta = atan(sxy2.x/sxy2.y);

        sxy3.x = post_data.data[4];
        sxy3.y = post_data.data[5];
        sxy3.theta = atan(sxy3.x/sxy3.y);

        sxy4.x = post_data.data[6];
        sxy4.y = post_data.data[7];
        sxy4.theta = atan(sxy4.x/sxy4.y);

        sxy5.x = post_data.data[8];
        sxy5.y = post_data.data[9];
        sxy5.theta = atan(sxy5.x/sxy5.y);

        sxy6.x = post_data.data[10];
        sxy6.y = post_data.data[11];
        sxy6.theta = atan(sxy6.x/sxy6.y);

        sxy7.x = post_data.data[12];
        sxy7.y = post_data.data[13];
        sxy7.theta = atan(sxy7.x/sxy7.y);

        sxy8.x = post_data.data[14];
        sxy8.y = post_data.data[15];
        sxy8.theta = atan(sxy8.x/sxy8.y);

        sxy9.x = post_data.data[16];
        sxy9.y = post_data.data[17];
        sxy9.theta = atan(sxy9.x/sxy9.y);

        sxy10.x = post_data.data[18];
        sxy10.y = post_data.data[19];
        sxy10.theta = atan(sxy10.x/sxy10.y);

        sxy11.x = post_data.data[20];
        sxy11.y = post_data.data[21]; 
        sxy11.theta = atan(sxy11.x/sxy11.y);      
    }

    void IbusCallback(const rc_msgs::IbusDataConstPtr& ibus_data)
    {
        ibus_.sw_a = ibus_data->sw_a;
        ibus_.sw_b = ibus_data->sw_b;
        ibus_.sw_c = ibus_data->sw_c;
        ibus_.sw_d = ibus_data->sw_d;
        ibus_.key_l = ibus_data->key_l;
        ibus_.key_r = ibus_data->key_r;
        ibus_.ch_l_x = ibus_data->ch_l_x;
        ibus_.ch_l_y = ibus_data->ch_l_y;
        ibus_.ch_r_x = ibus_data->ch_r_x;
        ibus_.ch_r_y = ibus_data->ch_r_y;
        ibus_.vr_a = ibus_data->vr_a;
        ibus_.vr_b = ibus_data->vr_b;
        // ROS_INFO("the ibus swa:%d,lx:%lf,ly:%lf", ibus_.sw_a,ibus_.ch_l_x,ibus_.ch_l_y);
    }
};
} //namespace rc_decision