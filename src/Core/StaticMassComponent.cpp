//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/StaticMassComponent.hpp"

//---
using namespace NPGTOS;

//---
Core::StaticMassComponent::StaticMassComponent() {
  this->init();
}

//---  
Core::StaticMassComponent::
  StaticMassComponent(double SystemMass, double Uncertainty, Core::UnitsT Unit) {
  
  #ifdef _WTF
  assert(Uncertainty>= 0.0);
  #endif
  
  this->systemMass.set(SystemMass, Uncertainty, Unit);
}
