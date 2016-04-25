#ifndef ROSCONDITION_H
#define ROSCONDITION_H

#include <ConditionNode.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <behavior_tree_core/BTAction.h>
namespace BT {
class ROSCondition : public ConditionNode {
public:
  // Constructor
  ROSCondition(std::string Name);
  ~ROSCondition();

  // The method that is going to be executed by the thread
  void Exec();
  behavior_tree_core::BTResult node_result;
  behavior_tree_core::BTGoal goal;
};
}

#endif
