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
        ROSAction* approach_pwc_left = new ROSAction("approach_pwc_left");
        ROSAction* approach_chassis_right = new ROSAction("approach_chassis_right");
        ROSAction* pick_pwc_left = new ROSAction("pick_pwc_left");
        ROSAction* pick_chassis_right = new ROSAction("pick_chassis_right");
        // ROSAction* assemble_pwc_chassis = new ROSAction("assemble_pwc_chassis");
        // ROSAction* place_chassis = new ROSAction("place_chassis");
        // ROSAction* transfer_left = new ROSAction("transfer_left");
        // ROSAction* is_chassis_in_left_eef = new ROSAction("is_chassis_in_left_eef");
        ROSCondition* is_chassis_in_right_eef = new ROSCondition("is_chassis_in_right_eef");
        ROSCondition* is_pwc_in_left_eef = new ROSCondition("is_pwc_in_right_eef");
        ROSCondition* is_left_eef_free = new ROSCondition("is_left_eef_free");
        ROSCondition* is_right_eef_free = new ROSCondition("is_right_eef_free");
        ROSCondition* is_left_eef_close_to_pwc = new ROSCondition("is_left_eef_close_to_pwc");
        ROSCondition* is_right_eef_close_to_chassis = new ROSCondition("is_right_eef_close_to_chassis");



        SequenceNode* sequence1 = new SequenceNode("seq1");
        SequenceNode* sequence2 = new SequenceNode("seq2");
        SequenceNode* sequence3 = new SequenceNode("seq3");
        SelectorNode* selector1 = new SelectorNode("sel1");
        SelectorNode* selector2 = new SelectorNode("sel2");
        SelectorNode* selector3 = new SelectorNode("sel3");
        SelectorNode* selector4 = new SelectorNode("sel4");

        sequence1->AddChild(selector1);
        sequence1->AddChild(selector3);

        selector1->AddChild(is_pwc_in_left_eef);
        selector1->AddChild(sequence2);

        sequence2->AddChild(is_left_eef_free);
        sequence2->AddChild(selector2);
        sequence2->AddChild(pick_pwc_left);

        selector2->AddChild(is_left_eef_close_to_pwc);
        selector2->AddChild(approach_pwc_left);

        selector3->AddChild(is_chassis_in_right_eef);
        selector3->AddChild(sequence3);

        sequence3->AddChild(is_right_eef_free);
        sequence3->AddChild(selector4);
        sequence3->AddChild(pick_chassis_right);

        selector4->AddChild(is_right_eef_close_to_chassis);
        selector4->AddChild(approach_chassis_right);


        Execute(sequence1, TickPeriod_milliseconds);//from BehaviorTree.cpp

}
    catch (BehaviorTreeException& Exception)
    {
        std::cout << Exception.what() << std::endl;
    }

return 0;
}
