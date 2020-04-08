#ifndef MAIN_CPP
#define MANI_CPP

#include <iostream>
#include "Person.hpp"
#include "Coords.hpp"

int main(int arc, char** argv){

  double t;
  int N = 24*2; // total hours
  
  // start with some people
  Person * personA = new Person();
  Person * personB = new Person();

  bool isInfected;

  // infect personA
  personA->setCoords(Coords(2.0,2.0));
  personA->becomeInfected(0.0,48.0);
  personB->setProbProt(0.8); // personal protection for personB

  for (int i = 0; i < N; ++i){
    t = (double)i; // simulation time
  
    isInfected = personB->contactWith(personA,t,0.1);
    std::cout << t << ": isInfected? " << isInfected << std::endl;

  }
  //std::cout << personA->estimateTrans(24.0) << std::endl;
  //std::cout << personA->calculateDist(personB->getCoords()) << std::endl;

  delete personA;
  delete personB;
  
  return 0;
}

#endif
