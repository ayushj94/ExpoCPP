#include <iostream>
#include "system.hpp"

void trigger(System * system, unsigned nodeId, int value);
void printStatus(System * system);

int main() {
  System system(7, "System");
  cout << system.name << ": started!\n";
  
  vector<unsigned> vect1{0, 1, 2, 3, 4, 5};
  system.nodes.at(0).updateQset(vect1);
  
  vector<unsigned> vect2{0, 1, 3, 4, 5};
  system.nodes.at(1).updateQset(vect2);
  
  vector<unsigned> vect3{1, 2, 3, 5, 6};
  system.nodes.at(2).updateQset(vect3);
  
  vector<unsigned> vect4{3, 4, 5, 6};
  system.nodes.at(3).updateQset(vect4);
  
  vector<unsigned> vect5{1, 3, 4};
  system.nodes.at(4).updateQset(vect5);
  
  vector<unsigned> vect6{60, 1, 2, 3, 5};
  system.nodes.at(5).updateQset(vect6);
  
  vector<unsigned> vect7{2, 3, 6};
  system.nodes.at(6).updateQset(vect7);
  
  system.startAll();
  trigger(&system, 5, 3);
  printStatus(&system);

  cout << "All test simulation finished!\n";
  return 0;
}

void trigger(System * sys, unsigned nodeID, int value) {
  sys->nodes[nodeID].nominate(value);
}

void printStatus(System * sys) {
  int iterations = 10;
  while(iterations > 0) {
    sys->printStatus();
    iterations--;
  }
  cout << sys->name << ": terminated!\n";
  cout << "\n";
}