//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/StoichioComponent.hpp"

//---
using namespace NPGTOS;

//---
Core::StoichioComponent::StoichioComponent() :
  Core::FactorizedComponent() {

  this->init();
}

//---
Core::StoichioComponent::
  StoichioComponent(double Factor,const Component* const ComponentRef) :
    Core::FactorizedComponent(Factor) {

  //this->FactorizedComponent::factor= Factor;
  
  this->componentRef= (Component*)ComponentRef;
}

//---
Core::StoichioComponent::~StoichioComponent() {
  this->init();
}
