//-*-c++-*-
#ifndef _NPGTOSCoreScalarQuantity_hpp
#define _NPGTOSCoreScalarQuantity_hpp

//---
//#include <iostream>

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Quantity.hpp"

//---
using namespace NPGTOS;

//---
class Core::ScalarQuantity final : public Core::Quantity {

  private :

    double value;
    
  protected :

    //virtual inline ScalarQuantity& set(double value, double Uncertainty, UnitsT Unit) final;

  public :

    ScalarQuantity();
    ScalarQuantity(double Value, double Uncertainty, UnitsT Unit);
    //~ScalarQuantity();

    virtual inline ScalarQuantity& copyToSQDest(ScalarQuantity& SQDest) const final;
    
    virtual inline double getValue() const final;
    virtual inline ScalarQuantity& setValue(double Value) final;

    virtual inline ScalarQuantity& unitAddConversion(double conversionAdd) final;
    virtual inline ScalarQuantity& unitFactorConversion(double conversionFactor) final;

    virtual inline ScalarQuantity& set(double value, double Uncertainty, UnitsT Unit) final;
};

//---
inline Core::ScalarQuantity& Core::ScalarQuantity::copyToSQDest(ScalarQuantity& SQDest) const {

  this->Quantity::copyToQDest(SQDest);

  SQDest.value= this->value;

  return SQDest;
}

//---
inline double Core::ScalarQuantity::getValue() const {
  return this->value;
}

//---
inline Core::ScalarQuantity&
  Core::ScalarQuantity::set(double Value, double Uncertainty, Core::UnitsT Unit) {

  #ifdef _WTF
  assert(Uncertainty>= 0.0);
  #endif  
  
  this->value= Value;
  this->Quantity::set(Uncertainty, Unit);
  
  return *this;
}

inline Core::ScalarQuantity& Core::ScalarQuantity::setValue(double Value) {

  this->value= Value;

  return *this;
}

//---
inline Core::ScalarQuantity&
  Core::ScalarQuantity::unitAddConversion(double conversionAdd) {
  
  this->value += conversionAdd;
  
  //--- No scale change here so no need to modify this->uncertainty
  
  return *this;  
}

//---
inline Core::ScalarQuantity& Core::ScalarQuantity::unitFactorConversion(double conversionFactor) {
  
  this->value *= conversionFactor;
  
  this->uncertainty *= conversionFactor;
  
  return *this;
}

#endif
