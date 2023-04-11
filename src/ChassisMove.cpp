//
// Created by jialonglong on 23-4-7.
//
#include <rc_decision/aurora/ChassisMove.h>

namespace rc_decision
{
    BT::NodeStatus ChassisMove::onStart() {
        ros::NodeHandle controller_nh("~");
        ros::NodeHandle root_nh;
        cmd_vel_pub_=root_nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
        if(!getInput<float>("Joy_LX",joy_lx_)||!getInput<float>("Joy_LY",joy_ly_)||
                !getInput<float>("Joy_RY",joy_ry_)){
            ROS_ERROR("Failed to get input");
            return BT::NodeStatus::IDLE;
        }
        else{
            controller_nh.getParam("linear_x_scale",linear_x_scale_);
            controller_nh.getParam("linear_y_scale",linear_y_scale_);
            controller_nh.getParam("angular_z_scale",angular_z_scale_);
            cmd_vel_.linear.x = joy_lx_ * linear_x_scale_;
            cmd_vel_.linear.y = joy_ly_ * linear_y_scale_;
            cmd_vel_.angular.z= joy_ry_ * angular_z_scale_;
            cmd_vel_pub_.publish(cmd_vel_);
            return BT::NodeStatus::SUCCESS;
        }
    }

    BT::NodeStatus ChassisMove::onRunning() {
        return BT::NodeStatus::RUNNING;
    }

    void ChassisMove::onHalted() {
        printf("[ ChassisMove: ABORTED ]");
    }

}