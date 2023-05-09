#include <ros/ros.h>
#include <rc_decision/aurora/laser_goal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <tf/transform_datatypes.h>
BT::NodeStatus rc_decision::laser_goal::onStart()
{
  if (!ac.waitForServer(ros::Duration(2.0)))
  {
    ROS_ERROR("Can't contact move_base server");
    return BT::NodeStatus::FAILURE;
  }

  if (!getInput<Pose2D>("Goal_point", goal_point))
  {
    throw BT::RuntimeError("missing required input [Goal_point]");
  }
  ROS_INFO("[ MoveBase: SEND REQUEST ]. goal: x=%f y=%f theta=%f\n", goal_point.x, goal_point.y, goal_point.theta);

  if (goal_point.x != 0 && goal_point.y != 0 && std::isfinite(goal_point.x) && std::isfinite(goal_point.y))
  {
    // Build the message from Pose2D
    move_base_msgs::MoveBaseGoal msg;
    msg.target_pose.header.frame_id = "map";
    msg.target_pose.header.stamp = ros::Time::now();
    msg.target_pose.pose.position.x = goal_point.x;
    msg.target_pose.pose.position.y = goal_point.y;
    // msg.target_pose.pose.position.x = 2;
    // msg.target_pose.pose.position.y = 1;
    msg.target_pose.pose.orientation.z = 0;
    msg.target_pose.pose.orientation.w = 1;

    // We use this counter to simulate an action that takes a certain
    // amount of time to be completed (200 ms)
    ac.sendGoal(msg);
    _aborted = false;
    while (!_aborted && !ac.waitForResult(ros::Duration(0.02)))
    {
      // polling at 50 Hz. No big deal in terms of CPU
    }
    if (_aborted)
    {
      // this happens only if method halt() was invoked
      //_client.cancelAllGoals();
      ROS_ERROR("MoveBase aborted");
      return BT::NodeStatus::FAILURE;
    }
    if (ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      ROS_ERROR("MoveBase failed");
      return BT::NodeStatus::FAILURE;
    }
    return BT::NodeStatus::RUNNING;
  }
  else
  {
    return BT::NodeStatus::SUCCESS;
  }
}

BT::NodeStatus rc_decision::laser_goal::onRunning()
{
  // Judge whether the position of the vehicle has arrived
  if (0.7 < abs(the_best_way.data[0]) < 0.9 && 0.8 < abs(the_best_way.data[1]) < 0.9)
  {
    ROS_INFO("Target reached");
    return BT::NodeStatus::SUCCESS;
  }
  return BT::NodeStatus::RUNNING;
}

void rc_decision::laser_goal::onHalted()
{
  printf("[ MoveBase: ABORTED ]");
}
