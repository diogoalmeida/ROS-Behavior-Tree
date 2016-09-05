cmake_minimum_required(VERSION 2.8.3)
project(behavior_tree_leaves)

find_package(catkin REQUIRED COMPONENTS
  genmsg
  actionlib_msgs
  actionlib
  message_generation
  roscpp
  roslib
  tf
  rospy
  std_msgs
  behavior_tree_core
  vrep_ros_interface
  roslaunch

)
roslaunch_add_file_check(launch)

find_package(Boost REQUIRED COMPONENTS system thread program_options)

add_definitions(-Wall -g -O0 -Wno-deprecated -static -Bstatic -std=gnu++0x)

catkin_package(
  CATKIN_DEPENDS actionlib_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(COMMON_LIB ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(ActionClient src/ActionClient.cpp)
target_link_libraries(
  ActionClient
  ${catkin_LIBRARIES}
)
add_dependencies(
 ActionClient
  ${behavior_tree_leaves_EXPORTED_TARGETS}
  ${PROJECT_NAME}_generate_messages_cpp
  behavior_tree_core_generate_messages_cpp
)

add_executable(ConditionClient src/ConditionClient.cpp)
target_link_libraries(
  ConditionClient
  ${catkin_LIBRARIES}
)
add_dependencies(
 ConditionClient
  ${behavior_tree_leaves_EXPORTED_TARGETS}
  ${PROJECT_NAME}_generate_messages_cpp
  behavior_tree_core_generate_messages_cpp
)

add_executable(ActionExample src/ActionExample.cpp)
target_link_libraries(
  ActionExample
  ${catkin_LIBRARIES}
)
add_dependencies(
 ActionExample
  ${behavior_tree_leaves_EXPORTED_TARGETS}
  ${PROJECT_NAME}_generate_messages_cpp
  behavior_tree_core_generate_messages_cpp
)

add_library(YumiApproachAction src/YumiApproachAction.cpp)
target_link_libraries(YumiApproachAction ${catkin_LIBRARIES})
add_dependencies(YumiApproachAction ${catkin_EXPORTED_TARGETS})

add_library(YumiPickAction src/YumiPickAction.cpp)
target_link_libraries(YumiPickAction ${catkin_LIBRARIES})
add_dependencies(YumiPickAction ${catkin_EXPORTED_TARGETS})

add_library(YumiAssembleAction src/YumiAssembleAction.cpp)
target_link_libraries(YumiAssembleAction ${catkin_LIBRARIES})
add_dependencies(YumiAssembleAction ${catkin_EXPORTED_TARGETS})

add_library(YumiPlaceAction src/YumiPlaceAction.cpp)
target_link_libraries(YumiPlaceAction ${catkin_LIBRARIES})
add_dependencies(YumiPlaceAction ${catkin_EXPORTED_TARGETS})

add_library(YumiTransferAction src/YumiTransferAction.cpp)
target_link_libraries(YumiTransferAction ${catkin_LIBRARIES})
add_dependencies(YumiTransferAction ${catkin_EXPORTED_TARGETS})

add_library(YumiIsXInEefCondition src/YumiIsXInEefCondition.cpp)
target_link_libraries(YumiIsXInEefCondition ${catkin_LIBRARIES})
add_dependencies(YumiIsXInEefCondition ${catkin_EXPORTED_TARGETS})

add_library(YumiCanEefAssembleCondition src/YumiCanEefAssembleCondition.cpp)
target_link_libraries(YumiCanEefAssembleCondition ${catkin_LIBRARIES})
add_dependencies(YumiCanEefAssembleCondition ${catkin_EXPORTED_TARGETS})

add_library(YumiCanEefReachXCondition src/YumiCanEefReachXCondition.cpp)
target_link_libraries(YumiCanEefReachXCondition ${catkin_LIBRARIES})
add_dependencies(YumiCanEefReachXCondition ${catkin_EXPORTED_TARGETS})

add_library(YumiIsEefCloseToXCondition src/YumiIsEefCloseToXCondition.cpp)
target_link_libraries(YumiIsEefCloseToXCondition ${catkin_LIBRARIES})
add_dependencies(YumiIsEefCloseToXCondition ${catkin_EXPORTED_TARGETS})

add_library(YumiAreEefCloseCondition src/YumiAreEefCloseCondition.cpp)
target_link_libraries(YumiAreEefCloseCondition ${catkin_LIBRARIES})
add_dependencies(YumiAreEefCloseCondition ${catkin_EXPORTED_TARGETS})

add_library(YumiIsEefFreeCondition src/YumiIsEefFreeCondition.cpp)
target_link_libraries(YumiIsEefFreeCondition ${catkin_LIBRARIES})
add_dependencies(YumiIsEefFreeCondition ${catkin_EXPORTED_TARGETS})

set(YumiActionImplementations
"YumiApproachAction"
"YumiPickAction"
"YumiAssembleAction"
"YumiPlaceAction"
"YumiTransferAction"
"YumiIsXInEefCondition"
"YumiCanEefAssembleCondition"
"YumiCanEefReachXCondition"
"YumiIsEefCloseToXCondition"
"YumiAreEefCloseCondition"
"YumiIsEefFreeCondition"
)

add_executable(YumiActions src/YumiActions.cpp)
target_link_libraries(YumiActions ${YumiActionImplementations} ${catkin_LIBRARIES})
add_dependencies(YumiActions ${catkin_EXPORTED_TARGETS})

add_executable(ConditionExample src/ConditionExample.cpp)
target_link_libraries(
  ConditionExample
  ${catkin_LIBRARIES}
)

add_dependencies(
 ConditionExample
  ${behavior_tree_leaves_EXPORTED_TARGETS}
  ${PROJECT_NAME}_generate_messages_cpp
  behavior_tree_core_generate_messages_cpp
)
