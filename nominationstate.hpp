#ifndef SCP_NOMINATIONSTATE_H
#define SCP_NOMINATIONSTATE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class LocalNode;
class ScpMessage;

class NominationState {
public:
    LocalNode * localNode;
    unsigned slotIndex;
    int x, y, z;
    map<unsigned, ScpMessage> n;
    bool confirmed;

    NominationState(LocalNode*, unsigned);
    void nominate(int);
    void voteOrAccept();
    ScpMessage getNominateMsg();
    void processMsg(ScpMessage);
    string getStatusString();
};

#endif //SCP_NOMINATIONSTATE_H
