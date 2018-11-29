#ifndef SCP_H
#define SCP_H

#include "system.hpp"
#include "localnode.hpp"

class SCP {
  public:
    static void trigger(System * system, unsigned nodeId, int val);
    static void printStatus(System * system);
};


#endif
