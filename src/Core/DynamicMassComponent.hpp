//-*-c++-*-
#ifndef _NPGTOSCoreDynamicMassComponent_hpp
#define _NPGTOSCoreDynamicMassComponent_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/ScalarQuantity.hpp"
#include "Core/StaticMassComponent.hpp"
//#include "Core/Nomenclature.hpp"

//---
using namespace NPGTOS;

//---
class Core::DynamicMassComponent final : public Core::StaticMassComponent {

  private:
  
  protected:
    
  public:

    DynamicMassComponent();
    DynamicMassComponent(double SystemMass, double Uncertainty, Core::UnitsT Unit);

    virtual inline DynamicMassComponent& setSystemMassValue(double SystemMassValue) final;
};

//---
inline Core::DynamicMassComponent&
  Core::DynamicMassComponent::setSystemMassValue(double SystemMassValue)  {

   #ifdef _WTF
  assert(SystemMassValue>=0.0);
  #endif
  
  this->systemMass.setValue(SystemMassValue);

  return *this;
}

#endif  
