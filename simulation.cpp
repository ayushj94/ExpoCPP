#include <iostream>
#include "simulation.hpp"
#include "system.hpp"
#include "scp.hpp"


void Simulation::simulate() {
  System system1(7, "System 1");
  cout << system1.name << ": started!\n";
  
  vector<unsigned> vect5{0, 1, 2, 3, 5};
  vector<unsigned> vect0{0, 1, 2, 3, 4, 5};
  system1.nodes.at(0)->updateQset(vect5);
  cout << "\nNode 0's qset: ";
  for (auto i = vect5.begin(); i != vect5.end(); ++i)
    std::cout << *i << ' ';

  vector<unsigned> vect1{0, 1, 3, 4, 5};
  system1.nodes.at(1)->updateQset(vect1);
  cout << "\nNode 1's qset: ";
  for (auto i = vect1.begin(); i != vect1.end(); ++i)
    std::cout << *i << ' ';
  
  vector<unsigned> vect2{1, 2, 3, 0, 6};
  system1.nodes.at(2)->updateQset(vect2);
  cout << "\nNode 2's qset: ";
  for (auto i = vect2.begin(); i != vect2.end(); ++i)
    std::cout << *i << ' ';
  
  vector<unsigned> vect3{3, 4, 0, 6};
  system1.nodes.at(3)->updateQset(vect3);
  cout << "\nNode 3's qset: ";
  for (auto i = vect3.begin(); i != vect3.end(); ++i)
    std::cout << *i << ' ';
  
  vector<unsigned> vect4{1, 3, 4};
  system1.nodes.at(4)->updateQset(vect4);
  cout << "\nNode 4's qset: ";
  for (auto i = vect4.begin(); i != vect4.end(); ++i)
    std::cout << *i << ' ';
  
  system1.nodes.at(5)->updateQset(vect0);
  cout << "\nNode 5's qset: ";
  for (auto i = vect0.begin(); i != vect0.end(); ++i)
    std::cout << *i << ' ';
  
  vector<unsigned> vect6{2, 3, 6};
  system1.nodes.at(6)->updateQset(vect6);
  cout << "\nNode 6's qset: ";
  for (auto i = vect6.begin(); i != vect6.end(); ++i)
    std::cout << *i << ' ';

  cout << "\n\n";

  SCP::trigger(&system1, 0, 3);
  cout<<"\n";
  if(system1.getStatus())
    cout << "System 1 reached preliminary consensus. Ready to move on to Ballot phase.\n";
  else
    cout << "System 1 is stuck\n";

  cout << "\n";

  System system2(10, "System 2");
  cout << system2.name << ": started!\n";
  system2.setHalfQset();
  SCP::trigger(&system2, 7, 4);
  cout<<"\n";
  if(system2.getStatus())
    cout << "System 2 reached preliminary consensus. Ready to move on to Ballot phase.\n";
  else
    cout << "System 2 is stuck\n";

}
