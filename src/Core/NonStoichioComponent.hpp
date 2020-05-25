//-*-c++-*-
#ifndef _NPGTOSCoreNonStoichioComponent_hpp
#define _NPGTOSCoreNonStoichioComponent_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Component.hpp"
#include "Core/StoichioComponent.hpp"
#include "Core/FactorizedComponent.hpp"

//---
using namespace NPGTOS;

//---
class Core::NonStoichioComponent final :
        public Core::FactorizedComponent {

  private:

    unsigned int nbRfs;

    //--- Non stoichiometric component is simply built from
    //    at least two StochioComponent objects references:
    //
    StoichioComponent** stchComponentsRfs;
  
    //std::vector<StoichioComponent *> stchComponentsRfs;
    
  protected:

    //virtual inline NonStoichioComponent& copy(NonStoichioComponent& target) const final;
    
    virtual inline NonStoichioComponent& init() final override;

  public:

    NonStoichioComponent();

    //--- TODO: constructor taking JSON data
    //NonStoichioComponent(unsigned int NbRfs, double Factor,
    //			 const Component** const restrict ComponentsRefs);
    
    ~NonStoichioComponent();    
};

// //---
// inline Core::NonStoichioComponent& Core::NonStoichioComponent::copy(NonStoichioComponent& target) const {

//   //#ifdef _WTF
//   //assert(this->componentRef);
//   //#endif

//   this->FactorizedComponent::copy(target);

//   this->stchComponentRef->copy(target.stchComponentRef);
  
//   return target;
// }

//---
inline Core::NonStoichioComponent& Core::NonStoichioComponent::init() {

  this->nbRfs= 0;
  
  this->stchComponentsRfs= NULL;
  //this->stchComponentsRefs.clear();

  return *this;
}

#endif

//--- Example of a non-stoichiometric solution phase representation:
//
// Pure Epidote: Ca2Fe3(SiO4)(Si2O7)O(OH)
//
//                     2*CaO + 1.5*Fe2O3 + 3*SiO2 + 0.5*H2O
//
// Oxygen items count: 2O   +   4.5O    + 6O   + 0.5O -> 13O
//
// ------------------------------------------------------------------------
//
// Pure Zoisite: Ca2Al3(SiO4)(Si2O7)O(OH)
//
//               2*CaO + 1.5*Al2O3 + 3*SiO2 + 0.5*H2O
//
// -------------------------------------------------------------------------
//
// Epidote-Zoisite solution phase : Ca2Al2{Fe3+;Al3+}(SiO4)(Si2O7)O(OH)
//
//                   2Ca2+, 2Al3+, {Fe3+,Al3+}, 3Si4+ : 25+
//
//                                          13O2-, H- : 25-
// -------------------------------------------------------------------------
//
//                   2*CaO + Al2O3 + { 1.5*Fe2O3, 1.5*Al2O3 } + 3*SiO2 + 0.5*H2O
//
//             NSC : 2*CaO + Al2O3 + 1.5*{ (1.0-x)*Fe2O3, x*Al2O3 } + 3*SiO2 + 0.5*H2O
//
// The entity { (1.0-x)*Fe2O3, x*Al2O3 } is a NonStoichioComponent(it could have more
// than two components in some cases) object and CaO, Al2O3, SiO2 and H2O are
// StoichioComponent objects.
//
