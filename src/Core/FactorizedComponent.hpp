//-*-c++-*-
#ifndef _NPGTOSCoreFactorizedComponent_hpp
#define _NPGTOSCoreFactorizedComponent_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
//#include "Core/StoichioComponent.hpp"

//---
using namespace NPGTOS;

//---
class Core::FactorizedComponent {

  protected:

    double factor;

  //virtual inline FactorizedComponent& copy(FactorizedComponent& target) const final;
  
    virtual inline FactorizedComponent& init();

  //virtual inline FactorizedComponent& setFactor(double Factor) final; 
  //virtual inline FactorizedComponent& set(double Factor,
  //					    double FactorLowerBound, double FactorUpperBound) final;
  
  public:

    FactorizedComponent();
    FactorizedComponent(double Factor);
  //  ~FactorizedComponent();

    virtual inline double getFactor() const final;
};

// //---
// inline Core::FactorizedComponent& Core::FactorizedComponent::copy(FactorizedComponent& target) const {
//   target.factor= this->factor;
//   return target;
// }

//---
inline double Core::FactorizedComponent::getFactor() const {
  return this->factor;
}

//---
inline Core::FactorizedComponent& Core::FactorizedComponent::init() {

  this->factor= 0.0;
  
  return *this;
}

// //---
// inline Core::FactorizedComponent& Core::FactorizedComponent::set(double Factor) {
//   this->factor= Factor;
  
//   return *this;  
// }

#endif
