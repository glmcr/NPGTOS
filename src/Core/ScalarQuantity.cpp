//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/ScalarQuantity.hpp"

//---
using namespace NPGTOS;

//---
Core::ScalarQuantity::ScalarQuantity() :
      Core::Quantity::Quantity() {

  this->value= 0.0;
}

//---
Core::ScalarQuantity::
  ScalarQuantity(double Value, double Uncertainty, Core::UnitsT Unit) :
    Core::Quantity::Quantity(Uncertainty, Unit) {

   this->value= Value;
}
