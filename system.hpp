#ifndef SCP_SYSTEM_H
#define SCP_SYSTEM_H

#include <string>
#include <vector>

using namespace std;

class LocalNode;
class ScpMessage;

class System {
public:
    string name;
    int nodeSize;
    vector<LocalNode*> nodes;

    System(unsigned, string);
    void setFullQset();
    void setHalfQset();
    void sendMsg(unsigned, ScpMessage);
    bool getStatus();
    void printStatus();
};


#endif //SCP_SYSTEM_H
