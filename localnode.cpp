#include "localnode.hpp"
#include "slot.hpp"
#include "system.hpp"
#include "scpmessage.hpp"

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

Slot* LocalNode::getSlot(unsigned slotIndex) {
    if (slotIndex < this->slots.size())
        return this->slots.at(slotIndex);
    else if (slotIndex == this->slots.size()) {
        this->slots.push_back(new Slot(this, slotIndex));
        return this->slots.at(slotIndex);
    } else
        return nullptr;
}

void LocalNode::nominate(int value, unsigned slotIndex) {
    getSlot(slotIndex)->nominate(value);
}

void LocalNode::sendMsg(ScpMessage msg, int toNodeId) {
    if (toNodeId >= 0) {
        system->sendMsg(toNodeId, msg);
    } else {
        for(unsigned i = 0; i < qSet.size() ; i++) {
            system->sendMsg(qSet.at(i), msg);
        }
    }
}

void LocalNode::processMsg(ScpMessage msg) {
    getSlot(msg.slotIndex)->processMsg(msg);
}

string LocalNode::getStatusString(unsigned slotIndex) {
    if(slotIndex < this->slots.size()) {
        Slot* slot = getSlot(slotIndex);
        return to_string(this->nodeId) + slot->getStatusString();
    } else {
        return to_string(this->nodeId) + "---";
    }
}