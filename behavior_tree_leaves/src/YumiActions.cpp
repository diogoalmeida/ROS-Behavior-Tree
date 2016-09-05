#include <behavior_tree_leaves/YumiApproachAction.h>
#include <behavior_tree_leaves/YumiPickAction.h>
#include <behavior_tree_leaves/YumiAssembleAction.h>
#include <behavior_tree_leaves/YumiPlaceAction.h>
#include <behavior_tree_leaves/YumiTransferAction.h>
#include <behavior_tree_leaves/YumiIsXInEefCondition.h>
#include <behavior_tree_leaves/YumiCanEefAssembleCondition.h>
#include <behavior_tree_leaves/YumiCanEefReachXCondition.h>
#include <behavior_tree_leaves/YumiIsEefCloseToXCondition.h>
#include <behavior_tree_leaves/YumiAreEefCloseCondition.h>
#include <behavior_tree_leaves/YumiIsEefFreeCondition.h>



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
  ApproachAction approach_chassis_right("approach_chassis_right", "Chassis", RIGHT, yumi);
  PickAction pick_chassis_right("pick_chassis_right", "Chassis", RIGHT, yumi);
  ApproachAction approach_pwc_right("approach_pwc_right", "PWC", RIGHT, yumi);
  PickAction pick_pwc_right("pick_PWX_right", "PWC", RIGHT, yumi);
  ApproachAction approach_pwc_left("approach_pwc_left", "PWC", LEFT, yumi);
  PickAction pick_pwc_left("pick_PWX_left", "PWC", LEFT, yumi);

  AssembleAction assemble_pwc_chassis("assemble_pwc_chassis", "PWC", "Chassis", yumi);
  PlaceAction place_chassis("place_chassis", "Chassis", yumi);
  TransferAction transfer_left("transfer_left", LEFT, yumi);
  TransferAction transfer_right("transfer_right", RIGHT, yumi);

  IsXInEefCondition is_chassis_in_left_eef("is_chassis_in_left_eef", "Chassis", LEFT, yumi);
  IsXInEefCondition is_chassis_in_right_eef("is_chassis_in_right_eef", "Chassis", RIGHT, yumi);
  IsXInEefCondition is_pwc_in_left_eef("is_pwc_in_left_eef", "PWC", LEFT, yumi);
  IsXInEefCondition is_pwc_in_right_eef("is_pwc_in_right_eef", "PWC", RIGHT, yumi);

  IsEefFreeCondition is_left_eef_free("is_left_eef_free", LEFT, yumi);
  IsEefFreeCondition is_right_eef_free("is_right_eef_free", RIGHT, yumi);

  CanEefAssembleCondition can_left_eef_assemble("can_left_eef_assemble", LEFT, yumi);
  CanEefAssembleCondition can_right_eef_assemble("can_left_eef_assemble", RIGHT, yumi);

  AreEefCloseCondition are_eef_close("are_eef_close", yumi);
  IsEefCloseToXCondition is_left_eef_close_to_pwc("is_left_eef_close_to_pwc", LEFT, "PWC", yumi);
  IsEefCloseToXCondition is_right_eef_close_to_chassis("is_right_eef_close_to_chassis", RIGHT, "Chassis", yumi);


  ros::spin();

  return 0;
}
