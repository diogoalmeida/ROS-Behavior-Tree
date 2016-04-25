#include <behavior_tree_leaves/ActionTemplate.h>

void ActionTemplate::executeCB(const behavior_tree_core::BTGoalConstPtr &goal) {
  ros::Rate r(execution_frequency_);
  ROS_INFO("Starting Action");

  while (ros::ok()) {
    // check that preempt has not been requested by the client
    if (action_server_.isPreemptRequested() || !ros::ok()) {
      ROS_INFO("Action Halted");

      preemptionRoutine();
      // set the action state to preempted
      action_server_.setPreempted();
      setStatus(FAILURE);
      break;
    }

    ROS_INFO("Executing Action");
    int success = executionRoutine();

    switch (success) {
    case 1:
      setStatus(SUCCESS);
      break;
    case -1:
      setStatus(FAILURE);
      break;
    }

    r.sleep();
  }
}

// returns the status to the client (Behavior Tree)
void ActionTemplate::setStatus(int status) {
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
    ROS_INFO("Action %s Succeeded", ros::this_node::getName().c_str());
    break;
  case FAILURE:
    ROS_INFO("Action %s Failed", ros::this_node::getName().c_str());
    break;
  default:
    break;
  }
}
