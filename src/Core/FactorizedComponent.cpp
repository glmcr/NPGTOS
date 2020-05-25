//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/FactorizedComponent.hpp"

//---
using namespace NPGTOS;

//---
Core::FactorizedComponent::FactorizedComponent() {
  this->init();
}

//---
Core::FactorizedComponent::FactorizedComponent(double Factor) {

  #ifdef _WTF
  assert(Factor>=0.0);
  #endif
  
  this->factor= Factor;
  //this->set(Factor);
}
