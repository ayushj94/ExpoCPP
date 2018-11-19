//
// Created by Ayush Jain on 18/11/18.
//

#include "nominationstate.hpp"
#include "localnode.hpp"

NominationState::NominationState(LocalNode * ln, int si) {
    localNode = ln;
    slotIndex = si;
    x = y = z= NULL;
    confirmed = false;
}