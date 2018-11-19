#ifndef EXPOCPP_NOMINATIONSTATE_H
#define EXPOCPP_NOMINATIONSTATE_H

#include <string>
#include <vector>

#include "scpmessage.hpp"

using namespace std;

class NominationState {
public:
    LocalNode * localNode;
    int slotIndex;
    int x, y, z;
    vector<ScpMessage> n;
    bool confirmed;

    NominationState(LocalNode *, int);
    void nominate(int);
    void voteOrAccept();
    ScpMessage getNominateMsg();
    void processMsg(ScpMessage);
    string getStatusString();
};

#endif //EXPOCPP_NOMINATIONSTATE_H
