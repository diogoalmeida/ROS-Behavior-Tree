#include "BehaviorTree.h"

using namespace BT;

int main(int argc, char **argv) {
  ros::init(argc, argv, "BehaviorTree");
  try {
    int TickPeriod_milliseconds = 1000;

    ROSAction *action1 = new ROSAction("A1");
    ROSAction *action2 = new ROSAction("A2");
    ROSCondition *condition = new ROSCondition("C1");

    SelectorNode *selector1 = new SelectorNode("sel1");
    SequenceNode *sequence1 = new SequenceNode("seq1");

    sequence1->AddChild(condition);
    sequence1->AddChild(action1);
    selector1->AddChild(sequence1);
    selector1->AddChild(action2);

    Execute(selector1, TickPeriod_milliseconds); // from BehaviorTree.cpp
  } catch (BehaviorTreeException &Exception) {
    std::cout << Exception.what() << std::endl;
  }

  return 0;
}
