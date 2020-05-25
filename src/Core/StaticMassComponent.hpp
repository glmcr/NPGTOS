//-*-c++-*-
#ifndef _NPGTOSCoreStaticMassComponent_hpp
#define _NPGTOSCoreStaticMassComponent_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Component.hpp"
#include "Core/ScalarQuantity.hpp"

//---
using namespace NPGTOS;

//---
class Core::StaticMassComponent : public Core::Component {

  //private:

  protected :
  
    ScalarQuantity systemMass; //--- Normally the % mass of a component in a system.
                               //    Here it is supposed to stay constant so this
                               //    class do not provide a public method to modify
                               //    its system mass.
  
  //virtual inline StaticMassComponent& init() final;
  
  public :

    StaticMassComponent();
    StaticMassComponent(double SystemMass, double Uncertainty, Core::UnitsT Unit);  
    //~StaticMassComponent();

    virtual inline double getSystemMassValue() const final;

    virtual inline StaticMassComponent& init(); // final override;
};

//---
inline double Core::StaticMassComponent::getSystemMassValue() const {
  return this->systemMass.getValue();
}

//---
inline Core::StaticMassComponent& Core::StaticMassComponent::init() {

  this->systemMass.set(0.0, 0.0, Core::UNDEFINED);

  return *this;
}

#endif
