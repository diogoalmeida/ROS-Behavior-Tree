#include <behavior_tree_leaves/YumiPlaceAction.h>

void PlaceAction::executeCB(const behavior_tree_core::BTGoalConstPtr &goal)
{
    bool success;
    // publish info to the console for the user
    ROS_INFO("Starting Action");
    if (as_.isPreemptRequested())
    {
      ROS_INFO("Action Halted");

      // set the action state to preempted
      as_.setPreempted();
    }
    ROS_INFO("Executing Action");
    success = yumi_->place(place_target_);

    if (success)
    {
        setStatus(SUCCESS);
    }
    else
    {
        setStatus(FAILURE);
    }
}

void PlaceAction::setStatus(int status){
  //Set The feedback and result of BT.action
  feedback_.status = status;
  result_.status = feedback_.status;
  // publish the feedback
  as_.publishFeedback(feedback_);
  // setSucceeded means that it has finished the action (it has returned SUCCESS or FAILURE).
  as_.setSucceeded(result_);

  switch(status){//Print for convenience
  case SUCCESS:
    ROS_INFO("Action %s Succeeded", ros::this_node::getName().c_str() );
    break;
  case FAILURE:
      ROS_INFO("Action %s Failed", ros::this_node::getName().c_str() );
    break;
  default:
    break;
  }
}
