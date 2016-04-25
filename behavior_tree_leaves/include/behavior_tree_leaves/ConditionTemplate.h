#ifndef __CONDITION_TEMPLATE__
#define __CONDITION_TEMPLATE__
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h> //actionlib
#include <behavior_tree_core/BTAction.h>

#ifndef __BT_STATUS__
#define __BT_STATUS__
enum Status { RUNNING, SUCCESS, FAILURE }; // BT return status
#endif

class ConditionTemplate {
protected:
  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<behavior_tree_core::BTAction> action_server_;
  std::string action_name_;
  behavior_tree_core::BTFeedback feedback_;
  behavior_tree_core::BTResult result_;

public:
  ConditionTemplate(std::string name)
      : action_server_(nh_, name,
                       boost::bind(&ConditionTemplate::executeCB, this, _1),
                       false),
        action_name_(name) {
    action_server_.start();
  }

  ~ConditionTemplate(void) {}

  void executeCB(const behavior_tree_core::BTGoalConstPtr &goal);
  void setStatus(int status);

  // This should return true or false quickly!
  virtual bool conditionEvaluation() = 0;
};
#endif
