#include "slot.hpp"

  Slot::Slot(LocalNode * localNode, unsigned slotIndex) {
    phase = "NOMINATE";
    this->localNode = localNode;
    this->slotIndex = slotIndex;
    this->nominationState = new NominationState(localNode, slotIndex);
  }

  void Slot::nominate(int value) {
    nominationState->nominate(value);
  }

  void Slot::processMsg(ScpMessage msg) {
    int nodeId = localNode->nodeId;
    int from = msg.nodeId;

    if(msg.type.compare("NOMINATE")) {
      if (phase.compare("NOMINATE")) {
        nominationState->processMsg(msg);
      } else {
        // prinf("Ignoring nomination message since this moved to ballot stage.");
      }
      return;
    } else {
      if (phase.compare("NOMINATE")) {
        nominationState->processMsg(msg);
        // this.phase == "PREPARE";
      }
      // ballotState->processMsg(msg);
    }
  }

  string Slot::getStatusString() {
    if (phase.compare("NOMINATE")) {
      return nominationState->getStatusString();
    }
    return "";
    // return this->ballotState->getStatusString();
  }
}