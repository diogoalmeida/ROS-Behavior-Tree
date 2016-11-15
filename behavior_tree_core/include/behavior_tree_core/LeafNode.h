#ifndef LEAFNODE_H
#define LEAFNODE_H

#include <vector>

#include <behavior_tree_core/TreeNode.h>

namespace BT {
class LeafNode : public TreeNode {
protected:
public:
  LeafNode(std::string Name);
  virtual ~LeafNode();
  void ResetColorState();
  int GetDepth();
};
}

#endif
