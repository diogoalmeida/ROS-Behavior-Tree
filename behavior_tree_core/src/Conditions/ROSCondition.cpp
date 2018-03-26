#include <behavior_tree_core/Conditions/ROSCondition.h>

using namespace BT;

enum Status { RUNNING, SUCCESS, FAILURE };

ROSCondition::ROSCondition(std::string Name)
    : ConditionNode::ConditionNode(Name) {
  Type = Condition;

  // Thread start
  Thread = boost::thread(&ROSCondition::Exec, this);
}

ROSCondition::~ROSCondition() {}

void ROSCondition::Exec() {
  bool action_server_started = false;
  ROS_INFO("Waiting For the Actuator %s to start", Name.c_str());

  actionlib::SimpleActionClient<behavior_tree_core::BTAction> ac(Name, true);
  action_server_started = ac.waitForServer(ros::Duration(2.0));

  if (action_server_started)
  {
    ROS_INFO("The Actuator %s has started", Name.c_str());
  }
  else
  {
    ROS_FATAL("The Actuator %s failed to start", Name.c_str());
    ros::shutdown();
  }

  behavior_tree_core::BTGoal goal;
  while (true) {

    // Waiting for a tick to come
    Semaphore.Wait();
    node_result.status = 0;

    ROS_INFO("I am running the request");

    if (ReadState() == Exit) {
      // The behavior tree is going to be destroied
      return;
    }

    // Condition checking and state update
    // do{
    if (action_server_started)
    {
      ac.sendGoal(goal);
      ac.waitForResult(ros::Duration(30.0));
      node_result = *(ac.getResult());
    }
    std::cout << " Condition Status" << node_result.status << "!" << std::endl;


    // }while(node_result.status != 2 && node_result.status != 1 ); //if it is
    // not halted and has not returned a status

    if (action_server_started)
    {
      if (node_result.status == SUCCESS) {
        SetNodeState(BT::Success);
        std::cout << Name << " returning Success" << Success << "!" << std::endl;
      } else if (node_result.status == FAILURE) {
        SetNodeState(BT::Failure);
        std::cout << Name << " returning Failure" << Failure << "!" << std::endl;
      } else {
        SetNodeState(BT::Failure);
        std::cout << Name << " returning NOTHING" << Failure << "!" << std::endl;
      }
    }
    else
    {
      SetNodeState(BT::Failure);
    }

    // Resetting the state
    WriteState(Idle);
  }
}
