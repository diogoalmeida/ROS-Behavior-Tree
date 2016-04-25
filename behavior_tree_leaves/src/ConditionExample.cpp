#include <ros/ros.h>
#include <behavior_tree_leaves/ConditionTemplate.h>

class BTCondition : ConditionTemplate {
public:
  BTCondition(std::string name) : ConditionTemplate(name), count_(0) {
    ROS_INFO("Condition Server Started");
  }
  ~BTCondition(void) {}

  bool conditionEvaluation() {
    count_++;

    if (count_ % 8 == 0) {
      return false;
    }
    return true;
  }

private:
  int count_;
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "condition");
  ROS_INFO("Enum: %d", RUNNING);
  ROS_INFO("Condition Ready for Ticks");
  BTCondition bt_condition(ros::this_node::getName());
  ros::spin();

  return 0;
}
