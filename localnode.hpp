#ifndef SCP_LOCALNODE_H
#define SCP_LOCALNODE_H

#include <vector>
#include <string>

using namespace std;

class Slot;
class ScpMessage;
class System;

class LocalNode {
    public:
        System * system;
        unsigned nodeId;
        vector<Slot*> slots;
        vector<unsigned> qSet;
        
        LocalNode(System *, unsigned);
        void updateQset(vector<unsigned>);
        vector<unsigned> cloneQset();
        void start();
        void tick();
        Slot* getSlot(unsigned);
        void nominate(int, unsigned = 0);
        void sendMsg(ScpMessage, int);
        void processMsg(ScpMessage);
        string getStatusString(unsigned = 0);
};

#endif //SCP_LOCALNODE_H
