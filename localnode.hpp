#ifndef SCP_LOCALNODE_H
#define SCP_LOCALNODE_H

#include <vector>
#include <string>

#include "system.hpp"
#include "slot.hpp"

class LocalNode {
    public:
        System * system;
        unsigned nodeId;
        vector<Slot> slots;
        vector<unsigned> qSet;
        
        LocalNode(System * system, unsigned nodeId);
        void updateQset(vector<unsigned> newQset);
        vector<unsigned> cloneQset();
        void start();
        void tick();
        Slot getSlot(unsigned slotIndex);
        void nominate(int value, unsigned slotIndex = 1);
        void sendMsg(ScpMessage msg, int toNodeId = -1);
        void processMsg(ScpMessage msg);
        string getStatusString(unsigned slotIndex = 1);
};

#endif //SCP_LOCALNODE_H
