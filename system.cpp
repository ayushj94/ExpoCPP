#include <iostream>

#include "system.hpp"

using namespace std;

System::System(unsigned nodeSize, string name) {
    this->name = name;
    this->nodeSize = nodeSize;
    for (unsigned i = 0; i < nodeSize; i++) {
        nodes.push_back(LocalNode(this, i));
    }
}

void System::setFullQset() {
    vector<unsigned> fullQuorumSet;
    for (unsigned i = 0; i < nodeSize; i++) {
        fullQuorumSet.push_back(i);
    }
    for (unsigned i = 0; i < nodeSize; i++) {
        nodes.at(i).updateQset(fullQuorumSet);
    }
}

void System::setHalfQset() {
    for (unsigned i = 0; i < nodeSize; i++) {
        vector<unsigned> qSet;
        for(unsigned j = i; j <= i + nodeSize / 2; j++) {
            qSet.push_back(j % nodeSize);
        }
        nodes[i].updateQset(qSet);
    }
}

void System::sendMsg(unsigned toNodeId, ScpMessage msg) {
    nodes.at(toNodeId).processMsg(msg);
}

// string System::getStatus() {
//     int value = -1;
//     string status = "Unknown";

//     for(unsigned i = 0 ; i < nodes.size(); i++) {
//         NominationState state = nodes.at(0).nominationState;
//             if (state.y >= 0) {
//                 if (value < 0) {
//                     value = state.y;
//                 }
//                 if (value == state.y) {
//                     status = "Agreed ";
//                 } else {
//                     status = "Stuck ";
//                 }
//             }
//         }
//     }
//     return status;
// }

void System::printStatus() {
    string s = "";
    for(unsigned i = 0 ; i <  nodes.size(); i++) {
        s += nodes.at(i).getStatusString();
    }
    string st = getStatus();
    cout << "Status: " + st + "Nodes: " + s;
}