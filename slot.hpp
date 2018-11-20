#ifndef SCP_SLOT_H
#define SCP_SLOT_H

#include <string>

#include "localnode.hpp"
#include "nominationstate.hpp"
#include "scpmessage.hpp"

using namespace std;

class Slot {
public:
    string phase;
    LocalNode * localNode;
    int slotIndex;
    NominationState * nominationState;

    Slot(LocalNode * localNode, unsigned slotIndex);
    void nominate(int value);
    void processMsg(ScpMessage msg);
    string getStatusString();
};

#endif //SCP_SLOT_H