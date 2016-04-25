#include <ros/ros.h>
#include <behavior_tree_leaves/ActionTemplate.h>

class BTAction : ActionTemplate {
public:
  BTAction(std::string name) : ActionTemplate(name) {}
  ~BTAction() {}

  void preemptionRoutine() {
    ROS_WARN("Action %s has been preempted", action_name_.c_str());
  }

  int executionRoutine() {
    ROS_INFO("Insert 0 to fail, otherwise, succeed");
    std::string input;
    char key;
    getline(std::cin, input);

    if (input.length() == 1) {
      key = input[0];
    } else {
      key = '1';
    }

    switch (key) {
    case '0':
      ROS_INFO("Action %s failed", action_name_.c_str());
      return -1;
    default:
      ROS_INFO("Action %s is being executed successfully",
               action_name_.c_str());
      return 1;
      break;
    }
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "action");
  ROS_INFO(" Enum: %d", RUNNING);
  ROS_INFO(" Action Ready for Ticks");
  BTAction bt_action(ros::this_node::getName());
  ros::spin();

  return 0;
}
