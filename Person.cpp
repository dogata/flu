#ifndef PERSON_CPP
#define PERSON_CPP

#include <iostream>
#include <cmath>
#include "Person.hpp"

Person::Person(double probTrans, double probRecov, double probMort, double probProt, double minDist, Coords coords)
  : mProbTrans(probTrans), mProbRecov(probRecov), mProbMort(probMort), mProbProt(probProt), mMinDist(minDist),
    mCoords(coords){
  std::random_device rd;
  mRand = std::mt19937(rd());
  if (probTrans > 0.0){
    mTInfected = 0.0;
  }
}

Person::Person()
  : mProbTrans(0.0), mProbRecov(0.0), mProbMort(0.0), mProbProt(0.0), mMinDist(1.83), mCoords(Coords()){
  std::random_device rd;
  mRand = std::mt19937(rd());
}

void Person::becomeRecovered(){
  // Recovered from infection
  mProbTrans = 0.0;
  mProbMort = 0.0;
  mProbRecov = 0.0;
}

void Person::becomeInfected(double ti, double tf){
  // Person becomes infected - sets time for recovery
  mTInfected = ti;
  mTRecov = tf;
  //infectDist = std::poisson_distribution<double>(tPeak);
}

double Person::estimateTransInternal(double t){
  // Transmission
  if ((t > mTRecov) || (t < mTInfected))
    return 0.0;
  return (mTRecov - t)/(mTRecov - mTInfected);
}

double Person::calculateDist(Coords coords){
  return std::sqrt(std::pow(mCoords.x-coords.x,2) + std::pow(mCoords.y-coords.y,2) + std::pow(mCoords.z-coords.z,2));
}

double Person::estimateTransDistance(double r){
  // Transmission due to physical distance
  if (r < mMinDist)
    return 1.0;
  return mMinDist/r;
}

double Person::estimateTransContactDuration(double dt){
  // Transmission due to contact duration
  if (dt > 24.0)
    return 1.0;
  return dt/24.0;
}

bool Person::contactWith(Person* person, double t, double dt){
  // Interact with person for a given duration
  // Transmission of person also depends on recovery time
  // Evaluate against personal protection
  
  double probTransInternal = person->estimateTransInternal(t);
  double probTransDistance = person->estimateTransDistance(calculateDist(person->getCoords()));
  double probTransContactDuration = estimateTransContactDuration(dt);
  double probTrans = probTransDistance*probTransInternal*probTransContactDuration;
    
  std::cout << "probTransInternal = " << probTransInternal
	    << " probTransDistance = " << probTransDistance
	    << " probTransContactDuration = " << probTransContactDuration
	    << " probTrans = " << probTrans*probTransDistance*probTransContactDuration <<std::endl;
  return (probTrans > mProbProt);
}

#endif
