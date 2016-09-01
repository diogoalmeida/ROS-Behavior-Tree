#include <behavior_tree_leaves/YumiApproachAction.h>
#include <behavior_tree_leaves/YumiPickAction.h>
#include <behavior_tree_leaves/YumiAssembleAction.h>
#include <behavior_tree_leaves/YumiPlaceAction.h>
#include <behavior_tree_leaves/YumiTransferAction.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "yumi_actions");
  ROS_INFO(" Enum: %d",RUNNING);
  ROS_INFO(" Action Ready for Ticks");
  vrep_ros_interface::Yumi *yumi;

  yumi = new vrep_ros_interface::Yumi();
  yumi->startSimulation();
  ApproachAction approach_chassis_left("approach_chassis_left", "Chassis", LEFT, yumi);
  PickAction pick_chassis_left("pick_chassis_left", "Chassis", LEFT, yumi);
  AssembleAction assemble_pwc_chassis("assemble_pwc_chassis", "PWC", "Chassis", yumi);
  PlaceAction place_chassis("place_chassis", "Chassis", yumi);
  TransferAction transfer_left("transfer_left", LEFT, yumi);

  ros::spin();

  return 0;
}
