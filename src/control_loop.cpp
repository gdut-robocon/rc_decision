/*
 * @Author: JIAlonglong
 * @Date: 2023-01-15 20:20:07
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-01-19 19:06:52
 * @FilePath: /rc_ws/src/rc_fsm/rc_decision/src/control_loop.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by JIAlonglong 2495477531@qq.com, All Rights Reserved. 
 */
#include <behaviortree_cpp_v3/loggers/bt_cout_logger.h>
#include <ros/ros.h>
#ifdef SUPPORT_OPENVINO
  #include "openvino_event.h"
#endif
#include <rc_decision/bt_service_node.h>
#include <rc_decision/bt_action_node.h>
#include <rc_decision/aurora/movebase_client.h>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "bt_tree");
    ros::NodeHandle nh("~");
    std::string xml_filename;
    //remember change path
    //unknown bug error in find path
    nh.param<std::string>("file", xml_filename,"/home/jialong03/rc_ws/src/rc_fsm/rc_decision/bt_xml/control_loop.xml");
    ROS_INFO("Loading XML : %s", xml_filename.c_str());

    //we use factory to register our custom nodes
    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<MoveBase>("MoveBase");
    
    auto tree = factory.createTreeFromFile(xml_filename);
    // Create a logger
    BT::StdCoutLogger logger_cout(tree);
    BT::NodeStatus status = BT::NodeStatus::IDLE;

    #ifdef ZMQ_FOUND
    // This logger publish status changes using ZeroMQ. Used by Groot
    PublisherZMQ publisher_zmq(tree);
    #endif

    // Keep on ticking until you get either a SUCCESS or FAILURE state
  while( ros::ok() && (status == BT::NodeStatus::IDLE || status == BT::NodeStatus::RUNNING))
  {
    ros::spinOnce();
    status = tree.tickRoot();
    std::cout << status << std::endl;
    
    ros::Duration sleep_time(0.01);
    sleep_time.sleep();
  }

  return 0;

    
}
