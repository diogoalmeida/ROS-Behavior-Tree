#ifndef SELECTORSTARNODE_H
#define SELECTORSTARNODE_H

#include <behavior_tree_core/ControlNode.h>

namespace BT {
class SelectorStarNode : public ControlNode {
public:
  // Constructor
  SelectorStarNode(std::string Name);
  ~SelectorStarNode();
  int GetType();
  // The method that is going to be executed by the thread
  void Exec();
};
}

#endif
