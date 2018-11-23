#ifndef SCP_SLOT_H
#define SCP_SLOT_H

#include <string>

class LocalNode;
class NominationState;
class ScpMessage;

using namespace std;

class Slot {
public:
    string phase;
    LocalNode * localNode;
    int slotIndex;
    NominationState * nominationState;

    Slot(LocalNode *, unsigned);
    void nominate(int);
    void processMsg(ScpMessage);
    string getStatusString();
};

#endif //SCP_SLOT_H