//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/NonStoichioComponent.hpp"

//---
using namespace NPGTOS;

//---
Core::NonStoichioComponent::NonStoichioComponent() :
     Core::FactorizedComponent::FactorizedComponent() {

  this->init();
}

// //---
// Core::NonStoichioComponent::
//   NonStoichioComponent(unsigned int NbRfs, double Factor,
// 		       const Component** const restrict ComponentsRfs) : Core::FactorizedComponent(Factor) {
//   //#ifdef _WTF
//   //assert(NbRfs>0);
//   //assert(ComponentsRfs);
//   //#endif
  
//   this->nbRfs= NbRfs;
//   this->stchComponentsRfs= new StoichioComponent[this->nbRfs];

//   for (int stc= 0; stc< NbRfs; stc++) {

//     //#ifdef _WTF
//     //assert(ComponentsRefs[stc]);
//     //#endif
    
//     this->stchComponentsRfs[stc]= ComponentsRefs[stc]; 
//   }

//   //for (int stc= 0; stc< NbRfs; stc++) {
//   //  //this->stchComponentsRefs.push_back( new StoichioComponent(0.0, ComponentsRefs[stc]) );
//   //}
// }

//---
Core::NonStoichioComponent::~NonStoichioComponent() {

  if ( this->stchComponentsRfs ) {
    
    for (int stc= 0; stc< this->nbRfs; stc++) {
      
      if (this->stchComponentsRfs[stc]) delete this->stchComponentsRfs[stc];
    }
    
    delete [] this->stchComponentsRfs;
  }
  
  //--- clear() is supposed to delete the objects contained
  //    in the vector.
  //this->stchComponentsRefs.clear();
  
  // for (auto cit= this->stchComponentsRefs.cbegin();
  //            cit!= this->stchComponentsRefs.cend(); cit++) { 
  //   delete *cit;
  // }
  
}

