#include <behavior_tree_core/SequenceNode.h>

using namespace BT;

SequenceNode::SequenceNode(std::string Name) : ControlNode::ControlNode(Name) {
  // Thread start
  Thread = boost::thread(&SequenceNode::Exec, this);
}

SequenceNode::~SequenceNode() {}

void SequenceNode::Exec() {
  unsigned int i;

  // Waiting for the first tick to come
  Semaphore.Wait();

  // Vector size initialization
  M = ChildNodes.size();
  // std::cout << Name << " has " << M << " children" << std::endl;

  // Simulating a tick for myself
  Semaphore.Signal();

  while (true) {
    // Waiting for a tick to come
    Semaphore.Wait();

    if (ReadState() == Exit) {
      // The behavior tree is going to be destroyed
      return;
    }

    // Checking if i was halted
    if (ReadState() != Halted) {
      // If not, the children can be ticked
      // std::cout << Name << " ticked, ticking children..." << std::endl;

      // For each child:
      for (i = 0; i < M; i++) {
        if (ChildNodes[i]->Type == Action) {
          // 1) if it's an action:
          // 1.1) read its state;
          // std::cout << "Reading child " << ChildNodes[i]->Name << std::endl;
          NodeState ActionState = ChildNodes[i]->ReadState();

          if (ActionState == Idle) {
            // 1.2) if it's "Idle":
            // 1.2.1) ticking it;
            // std::cout << "Child " << ChildNodes[i]->Name << " is Idle"
            //           << std::endl;
            ChildNodes[i]->Semaphore.Signal();

            // 1.2.2) retrieve its state as soon as it is available;
            ChildStates[i] = ChildNodes[i]->GetNodeState();
          } else if (ActionState == Running) {
            // 1.3) if it's "Running":
            // 1.3.1) saving "Running"
            ChildStates[i] = Running;
            // std::cout << "Child " << ChildNodes[i]->Name << " returned RUNNING"
            //           << std::endl;
          } else {
            // 1.4) if it's "Success" of "Failure" (it can't be "Halted"!):
            // 1.2.1) ticking it;

            if (ActionState == Success) {
              // std::cout << "Child " << ChildNodes[i]->Name
              //           << " returned SUCCESS" << std::endl;
            } else if (ActionState == Failure) {
              // std::cout << "Child " << ChildNodes[i]->Name
              //           << " returned FAILURE" << std::endl;
            }

            ChildNodes[i]->Semaphore.Signal();

            // 1.2.2) saving the read state;
            ChildStates[i] = ActionState;
          }
        } else {
          // 2) if it's not an action:
          // 2.1) ticking it;
          // std::cout << Name << " Ticking a control node!" << std::endl;
          ChildNodes[i]->Semaphore.Signal();

          // 2.2) retrive its state as soon as it is available;
          ChildStates[i] = ChildNodes[i]->GetNodeState();
        }

        // 3) if the child state is not a success:
        if (ChildStates[i] != Success) {
          // 3.1) the node state is equal to it;
          SetNodeState(ChildStates[i]);

          // 3.2) state reset;
          WriteState(Idle);

          // 3.3) all the next action or control child nodes must be halted:
          HaltChildren(i + 1);

          // 3.4) the "for" loop must end here.
          break;
        }
      }

      if (i == M) {
        // 4) if all of its children return "success":
        // 4.1) the node state must be "success";
        SetNodeState(Success);

        // 4.2) resetting the state;
        WriteState(Idle);

        // std::cout << Name << " returning Success!" << std::endl;
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

int SequenceNode::GetType() {
  // Lock acquistion

  return SEQUENCE;
}
