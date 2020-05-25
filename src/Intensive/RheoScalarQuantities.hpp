#ifndef _NPGTOSIntensiveRheoScalarQuantities_hpp
#define _NPGTOSIntensiveRheoScalarQuantities_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/ScalarQuantity.hpp"
#include "Intensive/Intensive.hpp"

//---
using namespace NPGTOS;

//---
class Intensive::RheoScalarQuantities {

  private :
  
  protected :

    Core::ScalarQuantity viscosity;
  //Core::ScalarQuantity bulkModulus;
  //Core::ScalarQuantity shearModulus;

    virtual inline RheoScalarQuantities& init();

  public :

    RheoScalarQuantities();
    //~RheoScalarQuantities();
    
    virtual inline Core::ScalarQuantity* const viscosityQ() const final;
};

//---
inline Core::ScalarQuantity*
  const Intensive::RheoScalarQuantities::viscosityQ() const {

    return (Core::ScalarQuantity* const) &this->viscosity;
}

//---
inline Intensive::RheoScalarQuantities&
  Intensive::RheoScalarQuantities::init() {

  this->viscosity.set(0.0, 0.0, Core::UNDEFINED);
  
  return *this;
}

#endif
