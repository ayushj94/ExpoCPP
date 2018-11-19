#ifndef EXPOCPP_NOMINATIONSTATE_H
#define EXPOCPP_NOMINATIONSTATE_H

#include <string>
#include <vector>
#include <map>

#include "scpmessage.hpp"

using namespace std;

class NominationState {
public:
    LocalNode * localNode;
    int slotIndex;
    int x, y, z;
    map<int, struct ScpMessage> n;
    bool confirmed;

    NominationState(LocalNode *, int);
    void nominate(int);
    void voteOrAccept();
    struct ScpMessage getNominateMsg();
    void processMsg(struct ScpMessage);
    string getStatusString();
};

#endif //EXPOCPP_NOMINATIONSTATE_H
