#ifndef EXPOCPP_SCPMESSAGE_H
#define EXPOCPP_SCPMESSAGE_H

#include <vector>
#include <string>

class LocalNode;

using namespace std;

struct ScpMessage {
    int nodeID;
    int slotIndex;
    string type;
    int x;
    int y;
    vector<LocalNode> qSet;
};

#endif //EXPOCPP_SCPMESSAGE_H
