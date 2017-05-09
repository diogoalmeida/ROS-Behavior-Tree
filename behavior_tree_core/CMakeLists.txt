cmake_minimum_required(VERSION 2.8.3)
project(behavior_tree_core)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  message_generation
  roscpp
  rospy
  std_msgs
  genmsg
)

add_action_files(
DIRECTORY action
FILES BT.action
)

generate_messages(
DEPENDENCIES actionlib_msgs std_msgs
)

include_directories(
include
${catkin_INCLUDE_DIRS}
)

catkin_package(
	DEPENDS GLUT OpenGL
	CATKIN_DEPENDS actionlib_msgs roscpp
	LIBRARIES behavior_tree
	INCLUDE_DIRS include
)

add_definitions(-Wall -lglut -lGL)

link_directories(${catkin_LIBRARY_DIRS})


#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

file(GLOB_RECURSE BTHeadLibrary include/behavior_tree_core/*.h)

set(BTSrcLibrary
src/ActionNode.cpp
src/ControlNode.cpp
src/ConditionNode.cpp
src/DecoratorRetryNode.cpp
src/DecoratorNegationNode.cpp
src/Draw.cpp
src/Exceptions.cpp
src/LeafNode.cpp
src/NodeSemaphore.cpp
src/ParallelNode.cpp
src/SelectorNode.cpp
src/SelectorStarNode.cpp
src/SequenceStarNode.cpp
src/TreeNode.cpp
src/SequenceNode.cpp
src/Actions/ActionTestNode.cpp
src/Actions/ROSAction.cpp
src/Conditions/ConditionTestNode.cpp
src/Conditions/ROSCondition.cpp
src/BehaviorTree.cpp
src/ROSLoaderNode.cpp
)

add_library(behavior_tree ${BTSrcLibrary} ${BTHeadLibrary})
target_link_libraries(behavior_tree ${catkin_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
add_dependencies(behavior_tree behavior_tree_core_generate_messages_cpp)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE)
