#include <iostream>
#include <algorithm>

#include <map>

#include "nominationstate.hpp"
#include "localnode.hpp"

using namespace std;

NominationState::NominationState(LocalNode * ln, int si) {
    localNode = ln;
    slotIndex = si;
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


    for (map<int, struct ScpMessage>::iterator it = n.begin(); it != n.end(); ++it)
    {
        struct ScpMessage msg = it->second;
        value = max(msg.x, msg.y);
        if (value == z) {
            votedOrAccepted[it->first] = value;
        }
        if (msg.y == z) {
            countAccepted++;
            for (vector<LocalNode>::iterator v_it = msg.qSet.begin(); v_it != msg.qSet.end(); ++v_it) {
                votedOrAccepted[(*v_it).nodeId] = msg.y;
            }
        }
    }

    int countVotedOrAccepted = 0;
    for (vector<LocalNode>::iterator v_it = (*localNode).qSet.begin(); v_it != (*localNode).qSet.end(); ++v_it) {
        if(!(votedOrAccepted.find((*v_it).nodeId) == votedOrAccepted.end())) {
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

struct ScpMessage NominationState::getNominateMsg() {
    struct ScpMessage msg;
    msg.nodeID = (*localNode).nodeId;
    msg.slotIndex = slotIndex;
    msg.type = "NOMINATE";
    msg.x = x;
    msg.y = y;
    for (int i = 0; i < (*localNode).qSet.size(); i++)
        msg.qSet.push_back((*localNode).qSet[i]);
    return msg;
}

void NominationState::processMsg(struct ScpMessage msg) {
    int nodeID = (*localNode).nodeId;
    int from = msg.nodeID;

    if (z < 0)
        z = max(msg.x, msg.y);

    for (vector<LocalNode>::iterator v_it = (*localNode).qSet.begin(); v_it != (*localNode).qSet.end(); ++v_it)
        if ((*v_it).nodeId == from)
            n[from] = msg;

    voteOrAccept();
}

string NominationState::getStatusString() {
    string s = "";
    s += (confirmed ? 'C' : (y >= 0 ? 'A' : (x >= 0 ? 'V' : (z >= 0 ? 'I' : '-'))));
    s += (z >= 0 ? z : '-');
    s += '-';
    return s;
}