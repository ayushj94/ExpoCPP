#include <iostream>
#include "scp.hpp"

using namespace std;

void SCP::trigger(System * sys, unsigned nodeID, int value) {
    sys->nodes[nodeID]->nominate(value);
}

void SCP::printStatus(System * sys) {
    int iterations = 10;
    while(iterations > 0) {
        sys->printStatus();
        iterations--;
    }
    cout << sys->name << ": terminated!\n";
    cout << "\n";
}
