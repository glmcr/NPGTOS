//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "System/Phase.hpp"

//---
//using namespace NPGTOS;

//---
System::Phase::Phase() :
  Core::Nomenclature::Nomenclature(),
  Extensive::Quantities::Quantities(),
  Intensive::SpecScalarQuantities::SpecScalarQuantities(),
  Intensive::RheoScalarQuantities::RheoScalarQuantities() {
  
  this->init();

  //this->updateNomenclature(NULL, NULL, NULL);
}

//---
System::Phase::~Phase() {

  //--- 
  this->eos.~Feed(); 
  
  if ( this->stchComponents ) free(this->stchComponents);
  if ( this->nonStchComponents ) free(this->nonStchComponents);

  this->init();
}
