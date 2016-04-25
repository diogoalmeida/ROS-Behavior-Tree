#include <ros/ros.h>
#include <behavior_tree_leaves/ActionTemplate.h>

class BTAction : ActionTemplate {
public:
  BTAction(std::string name) : ActionTemplate(name), count_(0) {}
  ~BTAction() {}

  void preemptionRoutine() {
    ROS_WARN("Action %s has been preempted", action_name_.c_str());
  }

  int executionRoutine() {
    count_++;

    if (count_ % 4 == 0) {
      return 1;
    }
    return -1;
  }

private:
  int count_;
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "action");
  ROS_INFO(" Enum: %d", RUNNING);
  ROS_INFO(" Action Ready for Ticks");
  BTAction bt_action(ros::this_node::getName());
  ros::spin();

  return 0;
}
