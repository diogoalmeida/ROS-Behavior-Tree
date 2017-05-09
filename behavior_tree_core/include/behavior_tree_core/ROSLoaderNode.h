#ifndef LOADERNODE_H
#define LOADERNODE_H

#include <ros/ros.h>
#include <behavior_tree_core/LeafNode.h>

namespace BT {
class ROSLoaderNode : public LeafNode {
public:
  // Constructor
  ROSLoaderNode(std::string Name);
  ~ROSLoaderNode();

  // The method that is going to be executed by the thread
  void Exec() = 0;

  // The method used to interrupt the execution of the node
  bool Halt();

  // Methods used to access the node state without the
  // conditional waiting (only mutual access)
  bool WriteState(NodeState StateToBeSet);
  int GetType();

  /**
    Pushes a new parameter into the parameter vectors.

    @param address The parameter address in the ROS parameter server.
    @param value The parameter value.
  **/
  void addParameter(const std::string &address, const std::string &value);
  void addParameter(const std::string &address, const int value);
  void addParameter(const std::string &address, const double value);

private:
  std::vector<std::string> string_addresses_, int_addresses_, double_addresses_, string_values_;
  std::vector<int> int_values_;
  std::vector<double> double_values_;

  /**
    Run through the parameters' vectors and load everything that is stored in memory.
  **/
  void loadParameters();
};
}

#endif
