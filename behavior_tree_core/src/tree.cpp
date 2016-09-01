#include "BehaviorTree.h"

using namespace BT;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "BehaviorTree");
    try
    {
        int TickPeriod_milliseconds = 1000;

        // ROSAction* action = new ROSAction("action");
        // ROSCondition* condition = new ROSCondition("condition");
        ROSAction* approach_chassis_left = new ROSAction("approach_chassis_left");
        ROSAction* pick_chassis_left = new ROSAction("pick_chassis_left");
        ROSAction* assemble_pwc_chassis = new ROSAction("assemble_pwc_chassis");
        ROSAction* place_chassis = new ROSAction("place_chassis");
        ROSAction* transfer_left = new ROSAction("transfer_left");

        //  SequenceNode* sequence1 = new SequenceNode("seq1");
        SequenceStarNode* sequence1 = new SequenceStarNode("seq1");

        sequence1->AddChild(approach_chassis_left);
        sequence1->AddChild(pick_chassis_left);
        sequence1->AddChild(assemble_pwc_chassis);
        sequence1->AddChild(place_chassis);
        sequence1->AddChild(transfer_left);

        Execute(sequence1, TickPeriod_milliseconds);//from BehaviorTree.cpp

}
    catch (BehaviorTreeException& Exception)
    {
        std::cout << Exception.what() << std::endl;
    }

return 0;
}
