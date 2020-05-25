//-*-c++-*-

//---
#include <cstring>

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Extensive/Quantities.hpp"

//---
using namespace NPGTOS;
//using namespace PMCTO::Core;

//---
Extensive::Quantities::Quantities() {
  this->init();  
}

//---
Extensive::Quantities& Extensive::Quantities::init() {

   memset(&this->quantities[0], 0x0, NB_EXT_QUANTITIES*sizeof(double));

  //this->mass.set(0.0, 0.0, Core::UNDEFINED);
  //for (int q= MASS; q< HELMHOLTZ_FE; q++ ) {
  //  this->quantities[q].set(0.0, 0.0, Core::UNDEFINED);
  //}
  
  return *this;
}
