#include <Actions/ActionTestNode.h>

using namespace BT;

ActionTestNode::ActionTestNode(std::string Name)
    : ActionNode::ActionNode(Name) {
  Type = Action;
  // Thread start
  Thread = boost::thread(&ActionTestNode::Exec, this);
}

ActionTestNode::~ActionTestNode() {}

void ActionTestNode::Exec() {

  while (true) {

    // Waiting for a tick to come
    Semaphore.Wait();

    if (ReadState() == Exit) { // SetColorState(Idle);

      // The behavior tree is going to be destroyed
      return;
    }

    // Running state
    SetNodeState(Running);
    std::cout << Name << " returning " << Running << "!" << std::endl;

    // Perform action...
    int i = 0;
    while (ReadState() == Running and i++ < 5) {
      std::cout << Name << " working!" << std::endl;
      boost::this_thread::sleep(boost::posix_time::milliseconds(800));
    }

    if (ReadState() == Exit) {
      // The behavior tree is going to be destroyed
      return;
    }

    else {
      // trying to set the outcome state:
      if (WriteState(status_) != true) {
        // meanwhile, my father halted me!
        std::cout << Name << " Halted!" << std::endl;

        // Resetting the state
        WriteState(Idle);

        // Next loop
        continue;
      }

      std::cout << Name << " returning " << Success << "!" << std::endl;
    }

    // Synchronization
    // (my father is telling me that it has read my new state)
    Semaphore.Wait();

    if (ReadState() == Exit) {

      // The behavior tree is going to be destroyed
      return;
    }

    // Resetting the state
    WriteState(Idle);
  }
}

bool ActionTestNode::Halt() {
  // Lock acquistion
  boost::lock_guard<boost::mutex> LockGuard(StateMutex);

  // Checking for "Running" correctness
  if (State != Running) {
    return false;
  }
  // SetColorState(Idle);

  State = Halted;
  return true;
}

void ActionTestNode::SetBehavior(NodeState status) { status_ = status; }
