//-*-c++-*-
#ifndef _NPGTOSCoreQuantity_hpp
#define _NPGTOSCoreQuantity_hpp

//---
//#include <iostream>

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"

//---
using namespace NPGTOS;

//---
class Core::Quantity {

  private :

  protected :

    UnitsT unit;
    double uncertainty;

    virtual inline Quantity& set(double Uncertainty, UnitsT Unit) final; 
  
  public :

    Quantity();
    Quantity(double Uncertainty, UnitsT Unit);
    //~Quantity();

    virtual inline Quantity& copyToQDest(Quantity& QDest) const;
  
    virtual inline UnitsT getUnit() const final;
    virtual inline double getUncertainty() const final;

    //inline std::string& getUnitName() const;
    //virtual inline Quantity& setUncertainty(double Uncertainty) final;
    //virtual inline Quantity& setUnit(double Unit) final;
};

//---
inline Core::Quantity& Core::Quantity::copyToQDest(Quantity& QDest) const {

  QDest.unit= this->unit;
  QDest.uncertainty= this->uncertainty;
  
  return QDest;
}

//--- 
inline double Core::Quantity::getUncertainty() const {
  return this->uncertainty;
}

//--- 
inline Core::UnitsT Core::Quantity::getUnit() const {
  return this->unit;
}

// //--- 
// inline Core::Quantity& Core::Quantity::setUncertainty(double Uncertainty) {
//   this->uncertainty= Uncertainty;
//   return *this;
// }

//---
inline Core::Quantity& Core::Quantity::set(double Uncertainty, Core::UnitsT Unit) {

  #ifdef _WTF
  assert(Uncertainty>= 0.0);
  #endif  
  
  this->uncertainty= Uncertainty;
  this->unit= Unit;
  
  return *this;
}

#endif
