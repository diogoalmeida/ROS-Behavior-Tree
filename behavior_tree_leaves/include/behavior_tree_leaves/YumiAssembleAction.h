#ifndef __YUMI_ASSEMBLE_ACTION__
#define __YUMI_ASSEMBLE_ACTION__
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>// needed for actionlib
#include <behavior_tree_core/BTAction.h>
#include <vrep_ros_interface/vrep_yumi_interface.h>

#ifndef __BT_ENUM__
#define __BT_ENUM__
enum Status {RUNNING,SUCCESS, FAILURE};//BT return status
#endif

class AssembleAction
{
protected:

  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise strange error may occur.
  actionlib::SimpleActionServer<behavior_tree_core::BTAction> as_;
  std::string action_name_, assemble_child_, assemble_parent_;
  // create messages that are used to published feedback/result
  behavior_tree_core::BTFeedback feedback_; //action feedback (SUCCESS, FAILURE)
  behavior_tree_core::BTResult result_;//action feedback  (same as feedback for us)
  vrep_ros_interface::Yumi *yumi_; // pointer to the yumi class


public:
  AssembleAction(std::string name, std::string assemble_child, std::string assemble_parent, vrep_ros_interface::Yumi *yumi) :
    as_(nh_, name, boost::bind(&AssembleAction::executeCB, this, _1), false),
    action_name_(name), assemble_child_(assemble_child), assemble_parent_(assemble_parent)
  {
   //Starts the action server
    as_.start();
    yumi_ = yumi;
  }

  ~AssembleAction(void)
  {
  }

  void executeCB(const behavior_tree_core::BTGoalConstPtr &goal);
  void setStatus(int status);
};

#endif
