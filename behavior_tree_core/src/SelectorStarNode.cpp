#include <behavior_tree_core/SelectorStarNode.h>

using namespace BT;

SelectorStarNode::SelectorStarNode(std::string Name)
    : ControlNode::ControlNode(Name) {
  // Thread start
  Thread = boost::thread(&SelectorStarNode::Exec, this);
}

SelectorStarNode::~SelectorStarNode() {}

void SelectorStarNode::Exec() {
  unsigned int i;

  // Waiting for the first tick to come
  Semaphore.Wait();

  // Vector size initialization
  M = ChildNodes.size();

  // Simulating a tick for myself
  Semaphore.Signal();
  i = 0; // Initialize the index of the child to tick

  while (true) {
    // Waiting for a tick to come
    Semaphore.Wait();

    if (ReadState() == Exit) {
      // The behavior tree is going to be destroied
      return;
    }

    // Checking if i was halted
    if (ReadState() != Halted) {
      // If not, the children can be ticked
      // std::cout << Name << " ticked, ticking children..." << std::endl;

      // For each child:
      while (i < M) {
        if (ChildNodes[i]->Type == Action) {
          // 1) if it's an action:
          // 1.1) read its state;
          NodeState ActionState = ChildNodes[i]->ReadState();

          if (ActionState == Idle) {
            // 1.2) if it's "Idle":
            // 1.2.1) ticking it;
            ChildNodes[i]->Semaphore.Signal();

            // 1.2.2) retrive its state as soon as it is available;
            ChildStates[i] = ChildNodes[i]->GetNodeState();
          } else if (ActionState == Running) {
            // 1.3) if it's "Running":
            // 1.3.1) saving "Running"
            ChildStates[i] = Running;
          } else {
            // 1.4) if it's "Success" of "Failure" (it can't be "Halted"!):
            // 1.2.1) ticking it;
            ChildNodes[i]->Semaphore.Signal();

            // 1.2.2) saving the read state;
            ChildStates[i] = ActionState;
          }
        } else {
          // 2) if it's not an action:
          // 2.1) ticking it;
          ChildNodes[i]->Semaphore.Signal();

          // 2.2) retrive its state as soon as it is available;
          ChildStates[i] = ChildNodes[i]->GetNodeState();
        }

        // 3) if the child state is not a success:
        if (ChildStates[i] != Failure) {

          // 3.1) the node state is equal to it;
          SetNodeState(ChildStates[i]);

          // 3.2) state reset;
          WriteState(Idle);
          if (ChildStates[i] == Success) {
            i = 0; // Final State of rhe selector node. Child index
                   // reinitialized
          }
          // 3.3) all the next action or control child nodes must be halted:
          // std::cout << Name << " returning " << ChildStates[i] << "!"
          //           << std::endl;

          // 3.4) the while loop must end here.
          break;
        } else if (ChildStates[i] == Failure) // if child i has failed the
                                              // selector star node can tick the
                                              // next child
        {
          i++;
        }
      }

      if (i == M) {
        // 4) if all of its children return "failure":
        // 4.1) the node state must be "failure";
        SetNodeState(Failure);
        i = 0;
        // 4.2) resetting the state;
        WriteState(Idle);

        // std::cout << Name << " returning " << Success << "!" << std::endl;
      }
    } else {
      // If it was halted, all the "busy" children must be halted too
      std::cout << Name << " halted! Halting all the children..." << std::endl;
      HaltChildren(0);
      // Resetting the node state
      WriteState(Idle);
    }
  }
}

int SelectorStarNode::GetType() {
  // Lock acquistion

  return SELECTORSTAR;
}
