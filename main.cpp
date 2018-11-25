#include <iostream>

#include "system.hpp"
#include "localnode.hpp"

void trigger(System * system, unsigned nodeId, int value);
void printStatus(System * system);

int main() {
  System system(7, "System");
  cout << system.name << ": started!\n";
  
  vector<unsigned> vect0{0, 1, 2, 3, 4, 5};
  system.nodes.at(0)->updateQset(vect0);
  cout << "\nNode 0's qset: ";
  for (auto i = vect0.begin(); i != vect0.end(); ++i)
    std::cout << *i << ' ';

  vector<unsigned> vect1{0, 1, 3, 4, 5};
  system.nodes.at(1)->updateQset(vect1);
  cout << "\nNode 1's qset: ";
  for (auto i = vect1.begin(); i != vect1.end(); ++i)
    std::cout << *i << ' ';
  
  vector<unsigned> vect2{1, 2, 3, 5, 6};
  system.nodes.at(2)->updateQset(vect2);
  cout << "\nNode 2's qset: ";
  for (auto i = vect2.begin(); i != vect2.end(); ++i)
    std::cout << *i << ' ';
  
  vector<unsigned> vect3{3, 4, 5, 6};
  system.nodes.at(3)->updateQset(vect3);
  cout << "\nNode 3's qset: ";
  for (auto i = vect3.begin(); i != vect3.end(); ++i)
    std::cout << *i << ' ';
  
  vector<unsigned> vect4{1, 3, 4};
  system.nodes.at(4)->updateQset(vect4);
  cout << "\nNode 4's qset: ";
  for (auto i = vect4.begin(); i != vect4.end(); ++i)
    std::cout << *i << ' ';
  
  vector<unsigned> vect5{0, 1, 2, 3, 5};
  system.nodes.at(5)->updateQset(vect5);
  cout << "\nNode 5's qset: ";
  for (auto i = vect5.begin(); i != vect5.end(); ++i)
    std::cout << *i << ' ';
  
  vector<unsigned> vect6{2, 3, 6};
  system.nodes.at(6)->updateQset(vect6);
  cout << "\nNode 6's qset: ";
  for (auto i = vect6.begin(); i != vect6.end(); ++i)
    std::cout << *i << ' ';

  cout << "\n\n";


  trigger(&system, 5, 3);
//   printStatus(&system);

  cout << "All test simulation finished!\n";
  return 0;
}

void trigger(System * sys, unsigned nodeID, int value) {
    sys->nodes[nodeID]->nominate(value);
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
