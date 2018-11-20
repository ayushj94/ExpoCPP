#include <iostream>

#include "system.hpp"

System::System(int nodeSize_, string name_) {
    name = name_;
    nodeSize = nodeSize_;
    for (int i = 0; i < nodeSize; i++) {
        nodes.push_back(new LocalNode(this));
    }
}

void System::setFullQset() {
    vector<LocalNode> fullQuorumSet;
    for (int i = 0; i < nodeSize; i++) {
        fullQuorumSet.push_back(nodes[i]);
    }
    for (int i = 0; i < nodeSize; i++) {
        nodes[i].updateQset(fullQuorumSet);
    }
}

void System::setHalfQset() {
    for (int i = 0; i < nodeSize; i++) {
        vector<LocalNode> qSet;
        for(int j = i; j <= i + nodeSize / 2; j++) {
            qSet.push_back(nodes[j % nodeSize]);
        }
        nodes[i].updateQset(qSet);
    }
}

void System::sendMsg(int to, struct ScpMessage msg) {
    nodes[to].processMsg(msg);
}

string System::getStatus() {
    int value = -1;
    string status = "Unknown";

    for (vector<LocalNode>::iterator v_it = nodes.begin(); v_it != nodes.end(); ++v_it) {
        if ((*v_it).slots.size() > 1) {
            NominationState state = (*v_it).slots[1].nominationState;
            if (state.y >= 0) {
                if (value < 0) {
                    value = state.y;
                }
                if (value == state.y) {
                    status = "Agreed ";
                } else {
                    status = "Stuck ";
                }
            }
        }
    }
    return status;
}

void System::printStatus() {
    string s = "";
    for (vector<LocalNode>::iterator v_it = nodes.begin(); v_it != nodes.end(); ++v_it) {
        s += (*v_it).getStatusString();
    }
    string st = getStatus();
    cout << "Status: " + st + "Nodes: " + s;
}