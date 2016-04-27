#ifndef DECORATORRETRYNODE_H
#define DECORATORRETRYNODE_H

#include <behavior_tree_core/ControlNode.h>

namespace BT {
class DecoratorRetryNode : public ControlNode {
public:
  // Constructor
  DecoratorRetryNode(std::string Name, unsigned int NTries);
  ~DecoratorRetryNode();
  int GetType();
  // The method that is going to be executed by the thread
  void Exec();

private:
  unsigned int NTries_;
  unsigned int TryIndx_;
};
}

#endif
