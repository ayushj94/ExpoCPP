#ifndef EXPOCPP_SLOT_H
#define EXPOCPP_SLOT_H

#include "nominationstate.hpp"

using namespace std;

class Slot {
public:
    string phase;
    LocalNode * localNode;
    int slotIndex;
    NominationState nominationState;

    Slot(LocalNode, int);
    void nominate(int);
    void processMsg(struct ScpMessage);
    string getStatusString();
};

#endif //EXPOCPP_SLOT_H