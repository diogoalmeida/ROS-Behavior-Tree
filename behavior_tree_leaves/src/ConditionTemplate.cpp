#include <ros/ros.h>
#include <behavior_tree_leaves/ConditionTemplate.h>

void ConditionTemplate::executeCB(
    const behavior_tree_core::BTGoalConstPtr &goal) {
  if (conditionEvaluation()) {
    setStatus(SUCCESS);
  } else {
    setStatus(FAILURE);
  }
}

// returns the status to the client (Behavior Tree)
void ConditionTemplate::setStatus(int status) {
  // Set The feedback and result of BT.action
  feedback_.status = status;
  result_.status = feedback_.status;
  // publish the feedback
  action_server_.publishFeedback(feedback_);
  // setSucceeded means that it has finished the action (it has returned
  // SUCCESS or FAILURE).
  action_server_.setSucceeded(result_);

  switch (status) { // Print for convenience
  case SUCCESS:
    ROS_INFO("Condition %s Succeeded", ros::this_node::getName().c_str());
    break;
  case FAILURE:
    ROS_INFO("Condition %s Failed", ros::this_node::getName().c_str());
    break;
  default:
    break;
  }
}
