//-*-c++-*-
#ifndef _NPGTOSExtensiveQuantities_hpp
#define _NPGTOSExtensiveQuantities_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/ScalarQuantity.hpp"
#include "Extensive/Extensive.hpp"

//---
using namespace NPGTOS;

//---
class Extensive::Quantities {

  protected :

    Core::ScalarQuantity quantities[NB_EXT_QUANTITIES];  //[QIndexT::HELMHOLTZ_FE+1];

    Quantities& init();
  
  public :

    Quantities();
   //~Quantities();

    virtual inline Core::ScalarQuantity* const getQuantity(QIndexT whichOne) const final;
  
    virtual inline Core::ScalarQuantity& setQuantityValue(double quantityValue, QIndexT whichOne) final;
};

//---
inline Core::ScalarQuantity* const Extensive::Quantities:: getQuantity(QIndexT whichOne) const { 

  //#ifdef _WTF
  //assert(0<=whichOne<NB_EXT_QUANTITIES);
  //#endif

  return (Core::ScalarQuantity* const) &this->quantities[whichOne]; 
}

//---
inline Core::ScalarQuantity&
  Extensive::Quantities::setQuantityValue(double quantityValue, QIndexT whichOne) { 

  //#ifdef _WTF
  //assert(0<=whichOne<NB_EXT_QUANTITIES);
  //#endif

   return this->quantities[whichOne].setValue(quantityValue); 
}

#endif
