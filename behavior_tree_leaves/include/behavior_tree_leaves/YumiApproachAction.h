#ifndef __YUMI_APPROACH_ACTION__
#define __YUMI_APPROACH_ACTION__
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>// needed for actionlib
#include <behavior_tree_core/BTAction.h>
#include <vrep_ros_interface/vrep_yumi_interface.h>

#ifndef __BT_ENUM__
#define __BT_ENUM__
enum Status {RUNNING,SUCCESS, FAILURE};//BT return status
#endif

class ApproachAction
{
protected:

  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise strange error may occur.
  actionlib::SimpleActionServer<behavior_tree_core::BTAction> as_;
  std::string action_name_, approach_target_;
  int eef_;
  // create messages that are used to published feedback/result
  behavior_tree_core::BTFeedback feedback_; //action feedback (SUCCESS, FAILURE)
  behavior_tree_core::BTResult result_;//action feedback  (same as feedback for us)
  vrep_ros_interface::Yumi *yumi_; // pointer to the yumi class


public:
  ApproachAction(std::string name, std::string approach_target, int eef, vrep_ros_interface::Yumi *yumi) :
    as_(nh_, name, boost::bind(&ApproachAction::executeCB, this, _1), false),
    action_name_(name), approach_target_(approach_target)
  {
   //Starts the action server
    as_.start();
    eef_ = eef;
    yumi_ = yumi;
  }

  ~ApproachAction(void)
  {
  }

  void executeCB(const behavior_tree_core::BTGoalConstPtr &goal);
  void setStatus(int status);
};

#endif
