#include <behavior_tree_core/ROSLoaderNode.h>

using namespace BT;

ROSLoaderNode::ROSLoaderNode(std::string Name) : LeafNode::LeafNode(Name) {
  Type = Condition;

  // Thread start
  Thread = boost::thread(&ROSLoaderNode::Exec, this);
}

ROSLoaderNode::~ROSLoaderNode() {}

bool ROSLoaderNode::Halt() { return true; }

bool ROSLoaderNode::WriteState(NodeState StateToBeSet) {

  if (StateToBeSet != Idle) {
    SetColorState(StateToBeSet);
  }
  // Lock acquistion
  boost::lock_guard<boost::mutex> LockGuard(StateMutex);

  State = StateToBeSet;
  return true;
}

int ROSLoaderNode::GetType() {
  // Lock acquistion

  return CONDITION;
}

void ROSLoaderNode::Exec() {
  while (true) {

    // Waiting for a tick to come
    Semaphore.Wait();

    if (ReadState() == Exit) {
      // The behavior tree is going to be destroied
      return;
    }

    // Condition checking and state update
    loadParameters();
    SetNodeState(Success);

    // Resetting the state
    WriteState(Idle);
  }
}

void ROSLoaderNode::addParameter(const std::string &address, const std::string &value){
  string_addresses_.push_back(address);
  string_values_.push_back(value);
}

void ROSLoaderNode::addParameter(const std::string &address, const int value){
  int_addresses_.push_back(address);
  int_values_.push_back(value);
}

void ROSLoaderNode::addParameter(const std::string &address, const double value){
  double_addresses_.push_back(address);
  double_values_.push_back(value);
}

void ROSLoaderNode::loadParameters(){
  for (int i = 0; i < string_addresses_.size(); i++)
  {
    ros::param::set(string_addresses_[i], string_values_[i]);
  }

  for (int i = 0; i < int_addresses_.size(); i++)
  {
    ros::param::set(int_addresses_[i], int_values_[i]);
  }

  for (int i = 0; i < double_addresses_.size(); i++)
  {
    ros::param::set(double_addresses_[i], double_values_[i]);
  }
}
