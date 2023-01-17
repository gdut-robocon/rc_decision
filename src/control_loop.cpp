/*
 * @Author: JIAlonglong
 * @Date: 2023-01-15 20:20:07
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-01-17 20:47:22
 * @FilePath: /rc_ws/src/rc_fsm/rc_decision/src/control_loop.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by JIAlonglong 2495477531@qq.com, All Rights Reserved. 
 */
#include <behaviortree_cpp_v3/loggers/bt_cout_logger.h>
#include <ros/ros.h>
#include <rc_decision/bt_service_node.h>
#include <rc_decision/bt_action_node.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "bt_tree");
    ros::NodeHandle nh("~");
    std::string xml_filename;
    nh.param<std::string>("file", xml_filename,"$(find rc_decision)/bt_xml/control_loop.xml");
    ROS_INFO("Loading XML : %s", xml_filename.c_str());

    //we use factory to register our custom nodes
    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<MoveBase>("MoveBase");
    factory.registerNodeType<ChassisCmd>("ChassisCommandVel");
    factory.registerNodeType<MoveToClosest>("MoveToClosest");
    
    auto tree = factory.createTreeFromFile(xml_filename);

    // Create a logger
    BT::StdCoutLogger logger_cout(tree);
    BT::NodeStatus status = BT::NodeStatus::RUNNING;
    // Keep on ticking until you get either a SUCCESS or FAILURE state
    while (ros::ok() && status == BT::NodeStatus::RUNNING) 
    {
    status = tree.rootNode()->executeTick();
    // Sleep 100 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

  return 0;

    
}
