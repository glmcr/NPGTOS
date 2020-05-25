//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Quantity.hpp"
//#include "Core/InlineQuantity.hpp"

//---
using namespace NPGTOS;

//---
Core::Quantity::Quantity() {

  this->set(0.0, Core::UNDEFINED);
}

//---
Core::Quantity::Quantity(double Uncertainty, Core::UnitsT Unit) {

  this->set(Uncertainty, Unit);
}

// //---
// Core::Quantity::Quantity(double Value, double Uncertainty, Core::UnitsT Unit) {
//   this->set(Value, Uncertainty, Unit);
//     //this->value= Value;
//     //this->uncertainty= Uncertainty;
//     //this->unit= Unit;
//   //this->setValue(Value);
//   //this->setUncertainty(Uncertainty);
// }
