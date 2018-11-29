#include <iostream>

#include "system.hpp"
#include "localnode.hpp"
#include "scpmessage.hpp"
#include "nominationstate.hpp"
#include "slot.hpp"

using namespace std;

System::System(unsigned nodeSize, string name) {
    this->name = name;
    this->nodeSize = nodeSize;
    for (unsigned i = 0; i < nodeSize; i++) {
        nodes.push_back(new LocalNode(this, i));
    }
}

void System::setFullQset() {
    vector<unsigned> fullQuorumSet;
    for (unsigned i = 0; i < nodeSize; i++) {
        fullQuorumSet.push_back(i);
    }
    for (unsigned i = 0; i < nodeSize; i++) {
        nodes.at(i)->updateQset(fullQuorumSet);
    }
}

void System::setHalfQset() {
    for (unsigned i = 0; i < nodeSize; i++) {
        vector<unsigned> qSet;
        for(unsigned j = i; j <= i + nodeSize / 2; j++) {
            qSet.push_back(j % nodeSize);
        }
        nodes[i]->updateQset(qSet);
    }
}

void System::sendMsg(unsigned toNodeId, ScpMessage msg) {
    nodes.at(toNodeId)->processMsg(msg);
}

bool System::getStatus() {
     int value = -1;
     bool status = false; //"Unknown";
     int confirmed_count = 0;
     for(unsigned i = 0; i < nodes.size(); i++) {
         NominationState* state = (nodes.at(i)->slots).at(0)->nominationState;
         if(state->confirmed)
            confirmed_count++;
        else
            cout << "!!!! Node " << i << " did not confirm !!!!\n";
        //  if (state->y >= 0) {
        //      if (value < 0) {
        //          value = state->y;
        //      }
        //      if (value == state->y) {
        //          status = "Agreed ";
        //      } else {
        //          status = "Stuck ";
        //      }
        //  }
     }
     return confirmed_count == nodes.size();
}

void System::printStatus() {
    string s = "";
    for(unsigned i = 0 ; i <  nodes.size(); i++) {
        s += nodes.at(i)->getStatusString(i);
    }
    string st = ""; //getStatus();
    cout << "Status: " + st + "Nodes: " + s << "\n";
}
