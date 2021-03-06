//-*-c++-*-
#ifndef _NPGTOSSystemPhase_hpp
#define _NPGTOSSystemPhase_hpp

//---
#include "NPGTOS.hpp"
#include "EoS/Feed.hpp"
#include "System/System.hpp"
#include "Core/Constants.hpp"
#include "Core/Nomenclature.hpp"
#include "Core/StoichioComponent.hpp"
#include "Core/NonStoichioComponent.hpp"

//---
#include "Extensive/Quantities.hpp"
#include "Intensive/SpecScalarQuantities.hpp"
#include "Intensive/RheoScalarQuantities.hpp"

//---
//using namespace NPGTOS;

//--- 
class System::Phase final :
  public Core::Nomenclature,
  public Extensive::Quantities,
  public Intensive::SpecScalarQuantities,
  public Intensive::RheoScalarQuantities {

  private :
  
  protected :

    //---
    SLGStateT slgState;   //--- SOLID, LIQUID, GASEOUS or SUPER_CRITICAL.
    ChemStateT chemState; //--- EQUILIBRIUM, META_EQUILIBRIUM or DISEQUILIBRIUM
    //StatusT status;

    //--- TODO: Use conditional compilation to
    //          be able to skip legacy Perple_X
    //          specific code ??
    // #ifdef _USE_PERPLE_X
    // EoS::PerpleXFeed eos;
    // #else
    
    EoS::Feed eos;
    
    // #endif
    
    //--- Create a class for component items encapsulation
    //    and make System::Phase class being a subclass of it ??
    Core::StoichioComponent* restrict stchComponents;
    Core::NonStoichioComponent* restrict nonStchComponents;
    
    //---      
    virtual inline Phase& init() final;
  
  public :

    Phase();
    ~Phase();
};

//---
inline System::Phase& System::Phase::init() {

  //this->activated= True;
  //this->nbComponents= 0;
  
  this->slgState= (SLGStateT) NPGTOS::UNDEFINED;
  this->chemState= (ChemStateT) NPGTOS::UNDEFINED;

  //this->whoAmI= NULL;
  
  this->stchComponents= NULL;
  this->nonStchComponents= NULL;

  this->eos.init();
  
  //const double gtest= this->eos.crunch(0.0,0.0); 
 
  return *this;
}

#endif
