#ifndef _NPGTOSIntensiveSpecScalarQuantities_hpp
#define _NPGTOSIntensiveSpecScalarQuantities_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/ScalarQuantity.hpp"
#include "Intensive/Intensive.hpp"

//---
using namespace NPGTOS;

//---
class Intensive::SpecScalarQuantities {

  private :
  
  protected :

    Core::ScalarQuantity volumicMass; //--- a.k.a. rho or density if you prefer.
    Core::ScalarQuantity heatCapacity;

    virtual inline SpecScalarQuantities& init();
    
  public :

    SpecScalarQuantities();
    //~SpecScalarQuantities();
    
    virtual inline Core::ScalarQuantity* const volumicMassQ() const final;
    virtual inline Core::ScalarQuantity* const heatCapacityQ() const final;

    //--- TODO: implemnent set methods ??
};

//---
inline Core::ScalarQuantity*
  const Intensive::SpecScalarQuantities:: volumicMassQ() const{

    return (Core::ScalarQuantity*) &this->volumicMass;
}

//---
inline Core::ScalarQuantity*
  const Intensive::SpecScalarQuantities::heatCapacityQ() const {

    return (Core::ScalarQuantity*) &this->heatCapacity;
}

//---
inline Intensive::SpecScalarQuantities&
  Intensive::SpecScalarQuantities::init() {

    this->volumicMass.set(0.0, 0.0, Core::UNDEFINED);
    this->heatCapacity.set(0.0, 0.0, Core::UNDEFINED);
  
    return *this;
}

#endif
