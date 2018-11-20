#ifndef SCP_SYSTEM_H
#define SCP_SYSTEM_H

#include <string>
#include <vector>

#include "localnode.hpp"
#include "scpmessage.hpp"

class System {
public:
    string name;
    int nodeSize;
    vector<LocalNode> nodes;

    System(unsigned nodeSize, string name);
    void setFullQset();
    void setHalfQset();
    void startAll();
    void sendMsg(unsigned toNodeId, ScpMessage msg);
    string getStatus();
    void printStatus();
};


#endif //SCP_SYSTEM_H