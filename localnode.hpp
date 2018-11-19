#ifndef EXPOCPP_LOCALNODE_H
#define EXPOCPP_LOCALNODE_H

using namespace std;

#include <vector>
#include <string>

#include "slot.hpp"

class System;

class LocalNode {
public:
    System * sys;
    int nodeID;
    vector<Slot> slots;
    vector<LocalNode> qset;

    LocalNode(System, int);
    void updateQset(vector<LocalNode>);
    vector<LocalNode> cloneQset();
    void start();
    void tick();
    Slot getSlot();
    void nominate(int);
    void sendMsg(ScpMessage, int);
    void processMsg(ScpMessage);
    string getStatusString();
};

#endif //EXPOCPP_LOCALNODE_H
