//-*-c++-*-
#ifndef _NPGTOSCoreStoichioComponent_hpp
#define _NPGTOSCoreStoichioComponent_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Component.hpp"
#include "Core/FactorizedComponent.hpp"

//---
using namespace NPGTOS;

//---
class Core::StoichioComponent final : public Core::FactorizedComponent {

  private:

    //--- Reference to only one Component object:
    //    NOTE: this pointer is not supposed to be modified
    //          after its initialization.
    //Component* componentRef;

  protected:

    //--- Reference to only one Component object:
    //    NOTE: this pointer is not supposed to be modified
    //          after its initialization.
    Component* componentRef;    

    //virtual inline StoichioComponent& copy(StoichioComponent& target) const final;
    
    virtual inline StoichioComponent& init() final override;

  public:

    StoichioComponent();
    StoichioComponent(double Factor,const Component* const ComponentRef);
    ~StoichioComponent();

    //virtual inline Component* const getComponentRef() const final;
};

////---
//inline Core::StoichioComponent& Core::StoichioComponent::copy(StoichioComponent& target) const {
//
//  //#ifdef _WTF
//  //assert(this->componentRef);
//  //#endif
//
//  this->FactorizedComponent::copy(target);
//
//  this->componentRef->copy(target.componentRef);
//  
//  return target;
//}

//---
inline Core::StoichioComponent& Core::StoichioComponent::init() {

  this->componentRef= NULL;

  return *this;
}

#endif
