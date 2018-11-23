#include <iostream>
#include <algorithm>

#include <map>

#include "nominationstate.hpp"
#include "localnode.hpp"
#include "slot.hpp"
#include "system.hpp"
#include "scpmessage.hpp"

using namespace std;

NominationState::NominationState(LocalNode * localNode, unsigned slotIndex) {
    this->localNode = localNode;
    this->slotIndex = slotIndex;
    x = y = z= -1;
    confirmed = false;
}

void NominationState::nominate(int value) {
    if (z < 0) {
        z = value;
    } else if (z != value) {
        // OK! no conflict.
        cout << "Ignore nominate command!";
        return;
    }
    voteOrAccept();
}

void NominationState::voteOrAccept() {
    bool needToSend = false;
    int countAccepted = 0;
    int value;
    map<int, int>votedOrAccepted = {};

    if (x < 0 && y < 0 && z >= 0) {
        x = z;
        needToSend = true;
    }


    for (map<unsigned int, ScpMessage>::iterator it = n.begin(); it != n.end(); ++it)
    {
        ScpMessage msg = it->second;
        value = max(msg.x, msg.y);
        if (value == z) {
            votedOrAccepted[it->first] = value;
        }
        if (msg.y == z) {
            countAccepted++;
            for(unsigned int i = 0 ; i < msg.qSet.size() ; i++) {
            // for (vector<LocalNode>::iterator v_it = msg.qSet.begin(); v_it != msg.qSet.end(); ++v_it) {
                votedOrAccepted[msg.qSet.at(i)] = msg.y;
            }
        }
    }

    int countVotedOrAccepted = 0;
    for(unsigned i = 0 ; i < localNode->qSet.size() ; i++) {
        if(!(votedOrAccepted.find(localNode->nodeId) == votedOrAccepted.end())) {
            countVotedOrAccepted++;
        }
    }

    if (y < 0) {
        if (countVotedOrAccepted >= ((*localNode).qSet.size() - 1)) {
            x = -1;
            y = z;
            needToSend = true;
        }
    }

    if (countAccepted >= ((*localNode).qSet.size() - 1))
        confirmed = true;

    if (needToSend)
        (*localNode).sendMsg(getNominateMsg(), -1);
}

ScpMessage NominationState::getNominateMsg() {
    ScpMessage msg;
    msg.nodeId = localNode->nodeId;
    msg.slotIndex = slotIndex;
    msg.type = "NOMINATE";
    msg.x = x;
    msg.y = y;
    msg.qSet = localNode->cloneQset();
    return msg;
}

void NominationState::processMsg(ScpMessage msg) {
    unsigned nodeId = localNode->nodeId;
    unsigned from = msg.nodeId;

    if (z < 0)
        z = max(msg.x, msg.y);

    for(unsigned i = 0 ; i < localNode->qSet.size() ; i++) {
        // for (vector<LocalNode>::iterator v_it = (*localNode).qSet.begin(); v_it != (*localNode).qSet.end(); ++v_it)
        if (localNode->qSet[i] == from)
            n[from] = msg;
    }

    voteOrAccept();
}

string NominationState::getStatusString() {
    string s = "";
    s += (confirmed ? 'C' : (y >= 0 ? 'A' : (x >= 0 ? 'V' : (z >= 0 ? 'I' : '-'))));
    s += (z >= 0 ? z : '-');
    s += '-';
    return s;
}