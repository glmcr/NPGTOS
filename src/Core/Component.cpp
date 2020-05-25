//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Component.hpp"

//---
using namespace NPGTOS;

//---
Core::Component::Component() : Core::Nomenclature::Nomenclature() {
  this->init();
}

//--- TODO: Use four JSON objects each with the three parameter
//          value, uncertainty, unit for this constructor 
//Core::Component::Component(double MolarMass, double ElemEntropy) {
//
//  //this->molarMass.set
//}
