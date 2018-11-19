#ifndef EXPOCPP_SYSTEM_H
#define EXPOCPP_SYSTEM_H

#include <string>
#include <vector>

#include "localnode.hpp"

class System {
public:
    string name;
    int nodeSize;
    vector<LocalNode> nodes;

    System(int, string);
    void setFullQset();
    void setHalfQset();
    void startAll();
    void sendMsg(int, struct ScpMessage);
    string getStatus();
    void printStatus();
};


#endif //EXPOCPP_SYSTEM_H