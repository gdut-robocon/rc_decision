#include <behaviortree_cpp_v3/loggers/bt_cout_logger.h>
#include <behaviortree_cpp_v3/behavior_tree.h>
#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/loggers/bt_zmq_publisher.h"
#include "behaviortree_cpp_v3/loggers/bt_minitrace_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_file_logger.h"
#include <ros/ros.h>
#ifdef SUPPORT_OPENVINO
  #include "openvino_event.h"
#endif
#include <rc_decision/bt_service_node.h>
#include <rc_decision/bt_action_node.h>
#include <rc_decision/aurora/movebase_client.h>
#include <rc_decision/aurora/lasermove_client.h>
#include <rc_decision/aurora/laser_goal.h>
#include <rc_decision/blackboard/blackboard.h>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "bt_tree");
    ros::NodeHandle nh("~");
    ros::NodeHandle root_nh;
    std::string xml_filename;
    //we use factory to register our custom nodes
    BT::BehaviorTreeFactory factory;
    
    factory.registerNodeType<rc_decision::MoveBase>("MoveBase");
    BT::NodeBuilder lasermove_build=[&root_nh,&nh](const std::string& name,const BT::NodeConfiguration& config){
      return std::make_unique<rc_decision::lasermove>(name,config,root_nh,nh);
    };
    factory.registerBuilder<rc_decision::lasermove>("lasermove",lasermove_build);

    factory.registerNodeType<rc_decision::laser_goal>("laser_goal"); 
    factory.registerNodeType<rc_decision::BlackboardRead>("BlackboardRead");



    std::string file_path = nh.param("file_path", std::string(" "));
    auto tree = factory.createTreeFromFile(file_path);
    ROS_INFO("Loading XML :%s", file_path.c_str());
    // Create a logger
    BT::StdCoutLogger logger_cout(tree);
    BT::NodeStatus status = BT::NodeStatus::IDLE;

    #ifdef ZMQ_FOUND
    // This logger publish status changes using ZeroMQ. Used by Groot
    PublisherZMQ publisher_zmq(tree);
    #endif

    // Keep on ticking until you get either a SUCCESS or FAILURE state
    ros::Rate loop_rate(5); 
  while( ros::ok())
  {
    status = tree.tickRoot();
    std::cout << status << std::endl;
    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;

    
}
