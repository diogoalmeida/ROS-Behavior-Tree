#ifndef CONDITIONTEST_H
#define CONDITIONTEST_H

#include <behavior_tree_core/ConditionNode.h>

namespace BT {
class ConditionTestNode : public ConditionNode {
public:
  // Constructor
  ConditionTestNode(std::string Name);
  ~ConditionTestNode();
  void SetBehavior(NodeState status);

  // The method that is going to be executed by the thread
  void Exec();

private:
  NodeState status;
};
}

#endif
