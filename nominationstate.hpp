#ifndef SCP_NOMINATIONSTATE_H
#define SCP_NOMINATIONSTATE_H

#include <string>
#include <vector>
#include <map>

#include "localnode.hpp"
#include "scpmessage.hpp"

using namespace std;

class NominationState {
public:
    LocalNode * localNode;
    unsigned slotIndex;
    int x, y, z;
    map<unsigned, ScpMessage> n;
    bool confirmed;

    NominationState(LocalNode* localNode, unsigned slotIndex);
    void nominate(int);
    void voteOrAccept();
    ScpMessage getNominateMsg();
    void processMsg(ScpMessage);
    string getStatusString();
};

#endif //SCP_NOMINATIONSTATE_H
