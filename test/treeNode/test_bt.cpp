/*
 * @Author: JIAlonglong
 * @Date: 2023-01-16 20:04:42
 * @LastEditors: JIAlonglong 2495477531@qq.com
 * @LastEditTime: 2023-01-16 20:52:27
 * @FilePath: /rc_ws/src/rc_fsm/rc_decision/test/treeNode/test_server.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by JIAlonglong 2495477531@qq.com, All Rights Reserved. 
 */
#include <rc_decision/bt_service_node.h>
#include <rc_decision/bt_action_node.h>
#include <ros/ros.h>
#include <rc_decision/AddTwoInts.h>
#include <rc_decision/FibonacciAction.h>

//this is a simple ActionNode to print robot's value

class PrintRobot : public BT::SyncActionNode
{
private:
    /* data */
public:
    PrintRobot(const std::string &name , const BT::NodeConfiguration& config):
        BT::SyncActionNode(name,config){}

    // you must override the virtual function tick()
    BT::NodeStatus tick() override
    {
        int value=0;
        if (getInput("message",value))
        {
            std::cout << "RBValue: " << value << std::endl;
            return BT::NodeStatus::SUCCESS;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
            return BT::NodeStatus::FAILURE;
        }
    }

    static BT::PortsList providedPort()
    {
        return {BT::InputPort<int>("message")};
    }    
};

// here you successfully build a ActionNode!

//a client Node example used in ros:
class AddTwoIntsAction : public RosServiceNode<rc_decision::AddTwoInts>
{
    public:
    AddTwoIntsAction(ros::NodeHandle& nh, const std::string& node_name, const NodeConfiguration & conf):
    RosServiceNode<rc_decision::AddTwoInts>(nh, node_name, conf){}

    static BT::PortsList providedPorts()
    {
        return{
            InputPort<int>("first int");
            InputPort<int>("second_int");
            OutputPort<int>("sum");
        }

    }

    void sendRequest(RequestType& request) override
    {
        getInput("first_int",request.a);
        getInput("second_int",request.b);
        expected_result_= request.a + request.b;
        ROS_INFO("AddTwoInts: sending request ");
    }

    NodeStatus onResponse(const ResponseType& rep) override
    {
        ROS_INFO("AddTwoInts: response received");
        if (rep.sum == expected_result_)
        {
            setOutput<int>("sum",rep.num);
            return BT::NodeStatus::SUCCESS;
        }
        else
        {
            ROS_ERROR("AddTwoInts replied something unexpected: %d",rep.num);
            return BT::NodeStatus::FAILURE;
        }
        
        
    }

    virtual NodeStatus onFailedRequest(RosServiceNode::FailureCause failure)override
    {
        ROS_ERROR("AddTwoInts request failed %d", static_cast<int>(failure));
        return BT::NodeStatus::FAILURE;
    }

private:
 int expected_result_; 
};