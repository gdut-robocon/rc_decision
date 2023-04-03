/*
 * @Author: robox-xx 1399786770@qq.com
 * @Date: 2023-03-15 11:04:27
 * @LastEditors: robox-xx 1399786770@qq.com
 * @LastEditTime: 2023-04-03 14:19:33
 * @FilePath: /rc_ws/src/rc_decision/include/rc_decision/blackboard/blackboard.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include <rc_decision/bt_action_node.h>
#include <rc_decision/bt_service_node.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <std_msgs/Float64MultiArray.h>

using namespace std;
// struct Pose2D
// {
//   double x, y, theta;
// };

namespace rc_decision
{
class BlackboardRead : public BT::SyncActionNode
{
    public:
    BlackboardRead(const std::string& name, const BT::NodeConfiguration& config): BT::SyncActionNode(name, config)
    {
        ros::NodeHandle nh;
        radar_tf_data = nh.subscribe("the_shoot_position", 5, &BlackboardRead::LadarCallback, this);
    };
    
    //Initialization of keys
    static BT::PortsList providedPorts() {
        BT::PortsList ports_list;   
        ports_list.insert(BT::OutputPort<Pose2D>("Goal"));
        return ports_list;
    }

    //Adding data to the blackboard
    BT::NodeStatus tick() override {
    
        setOutput("Goal", goal);
        ROS_INFO("ii sss xxx:%f, yyy:%f", goal.x,goal.y);
        
        return BT::NodeStatus::SUCCESS;
    };



    private:
    
    ros::Subscriber radar_tf_data;
    Pose2D goal;

    void LadarCallback(const std_msgs::Float64MultiArray msg)
   {
    goal.x=msg.data[0];
    goal.y=msg.data[1];  
    goal.theta = atan(goal.x/goal.y);
    printf("msg is %lf", msg.data[0]);
   }
};
} //namespace rc_decision