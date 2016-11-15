#include <behavior_tree_core/Conditions/ConditionTestNode.h>

using namespace BT;

ConditionTestNode::ConditionTestNode(std::string Name)
    : ConditionNode::ConditionNode(Name) {
  Type = Condition;

  // Thread start
  Thread = boost::thread(&ConditionTestNode::Exec, this);
}

ConditionTestNode::~ConditionTestNode()
{
  std::cout << Name << " is being destroyed" << std::endl;
  Thread.interrupt();
  Thread.join();
}

void ConditionTestNode::Exec() {
  int i = 0;
  while (true) {

    // Waiting for a tick to come
    Semaphore.Wait();

    if (ReadState() == Exit) {
      // The behavior tree is going to be destroied
      return;
    }

    // Condition checking and state update
    i++;
    if (i < 5) {
      SetNodeState(Success);
      std::cout << Name << " returning Success" << Success << "!" << std::endl;
    } else if (i < 10) {
      SetNodeState(Failure);
      std::cout << Name << " returning Failure" << Failure << "!" << std::endl;
    } else {
      std::cout << Name << " reset i!" << std::endl;
      SetNodeState(Failure);
      i = 0;
    }

    // Resetting the state
    WriteState(Idle);
  }
}
