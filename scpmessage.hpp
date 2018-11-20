#ifndef SCP_SCPMESSAGE_H
#define SCP_SCPMESSAGE_H

#include <vector>
#include <string>

using namespace std;

class ScpMessage {
    public:
        unsigned nodeId;
        unsigned slotIndex;
        string type;
        int x;
        int y;
        vector<unsigned> qSet;
};

#endif //SCP_SCPMESSAGE_H
