#ifndef PERSON_HPP
#define PERSON_HPP
// Person class

#include <random>
#include "Coords.hpp"

class Person {
 private:
  double mProbTrans; // transmission probability
  double mProbRecov; // recovery probability
  double mProbMort; // mortality probability
  double mProbProt; // protection probability
  double mTInfected; // infected time
  double mTRecov; // time until full recover
  double mMinDist; // minimum distance to contract

  Coords mCoords; // physical coordinates of person
  
  std::mt19937 mRand; // random number generator
  //std::poisson_distribution<double> infectDist; // severity of infection distribution
 public:
  Person();
  Person(double probTrans, double probRecov, double probMort, double probProt, double minDist, Coords coords);
  ~Person(){}

  // setters
  void setProbTrans(double probtrans){ mProbTrans = probtrans; }
  void setProbRecov(double probRecov){ mProbRecov = probRecov; }
  void setProbMort(double probMort){ mProbMort = probMort; }
  void setProbProt(double probProt){ mProbProt = probProt; }
  void setMinDist(double minDist){ mMinDist = minDist; }
  void setCoords(Coords coords){ mCoords = coords; }

  // getters
  Coords getCoords(){ return mCoords; }
  bool isInfected()( return (mProbTrans > 0.0); }
  
  // Received infection - specifies how the body reacts; can be modeled in more detailed
  void becomeInfected(double ti, double tf);
  
  // Determine severity of transmission from infected individual depending on time
  double estimateTransInternal(double t);

  // Transmission due to physical distance
  double estimateTransDistance(double r);

  // Transmission due to duration of contact
  double estimateTransContactDuration(double dt);

  // Returns probability from Poisson distribution
  double estimatePoissonProb(double lambda);

  // Calculates distance between a given coordinates and person
  double calculateDist(Coords coords);
  


  // Interact with other people
  bool contactWith(Person* person, double t, double dt);
  
  // Evaluates if person is infected
};

#endif
