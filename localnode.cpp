//
// Created by Ayush Jain on 18/11/18.
//

#include "localnode.hpp"

using namespace std;

LocalNode::LocalNode(System * system, unsigned nodeId) {
  this->system = system;
  this->nodeId = nodeId;
}

void LocalNode::updateQset(vector<unsigned> newQset) {
  this->qSet = newQset;
}

vector<unsigned> LocalNode::cloneQset() {
  return this->qSet;
}

Slot LocalNode::getSlot(unsigned slotIndex) {
  return this->slots.at(slotIndex);
}

void LocalNode::nominate(int value, unsigned slotIndex) {
  getSlot(slotIndex).nominate(value);
}

void LocalNode::sendMsg(ScpMessage msg, int toNodeId) {
  if(toNodeId >= 0) {
    system->sendMsg(toNodeId, msg);
  } else {
    for(unsigned i = 0; i < qSet.size() ; i++) {
      system->sendMsg(qSet.at(i), msg);
    }
  }
}

void LocalNode::processMsg(ScpMessage msg) {
  getSlot(msg.slotIndex).processMsg(msg);
}

string LocalNode::getStatusString(unsigned slotIndex) {
  if(slotIndex < this->slots.size()) {
    Slot slot = getSlot(slotIndex);
    return to_string(this->nodeId) + slot.getStatusString();
  } else {
    return to_string(this->nodeId) + "---";
  }

}