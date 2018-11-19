#ifndef EXPOCPP_LOCALNODE_H
#define EXPOCPP_LOCALNODE_H

#include <vector>
#include <string>

#include "slot.hpp"

class System;

class LocalNode {
public:
    System * sys;
    int nodeId;
    vector<Slot> slots;
    vector<LocalNode> qSet;

    LocalNode(System, int);
    void updateQset(vector<LocalNode>);
    vector<LocalNode> cloneQset();
    void start();
    void tick();
    Slot getSlot();
    void nominate(int);
    void sendMsg(struct ScpMessage, int);
    void processMsg(struct ScpMessage);
    string getStatusString();
};

#endif //EXPOCPP_LOCALNODE_H
