#ifndef __YUMI_CAN_EEF_REACH_X_CONDITION__
#define __YUMI_CAN_EEF_REACH_X_CONDITION__
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>//actionlib
#include <behavior_tree_core/BTAction.h>
#include <vrep_ros_interface/vrep_yumi_interface.h>

#ifndef __BT_ENUM__
#define __BT_ENUM__
enum Status {RUNNING,SUCCESS, FAILURE};//BT return status
#endif

class CanEefReachXCondition
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<behavior_tree_core::BTAction> as_;
  std::string condition_name_, object_name_;
  int eef_;
  // create messages that are used to published feedback/result
  behavior_tree_core::BTFeedback feedback_; //action feedback (SUCCESS, FAILURE)
  behavior_tree_core::BTResult result_;//action feedback  (same as feedback for us)
  vrep_ros_interface::Yumi *yumi_; // pointer to the yumi class


public:
  CanEefReachXCondition(std::string name,int eef, std::string object_name, vrep_ros_interface::Yumi *yumi) :
    as_(nh_, name, boost::bind(&CanEefReachXCondition::executeCB, this, _1), false),
    condition_name_(name), object_name_(object_name)
  {
   //Starts the action server
    as_.start();
    eef_ = eef;
    yumi_ = yumi;
  }

  ~CanEefReachXCondition(void)
  {
  }

  void executeCB(const behavior_tree_core::BTGoalConstPtr &goal);
  void setStatus(int status);
};

#endif
