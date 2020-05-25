//-*-c++-*-
#ifndef _NPGTOSSystemStaticLineup_hpp
#define _NPGTOSSystemStaticLineup_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Constants.hpp"
#include "System/System.hpp"
#include "System/Phase.hpp"

//---
using namespace NPGTOS;

//---
class System::StaticLineup {

  private :
  
  protected :
  
    //--- Since the total number of Phase objects
    //    is known at the beggining then we can use 
    //    an allocatable array(which is supposed to
    //    be allocated only once at the beginning
    //    of the computations) to store them. These
    //    Phase objects represent all the possible
    //    known real phases allowed by the components
    //    system used(NCKFMASHTO for example)
    System::Phase* restrict phases;

    virtual inline StaticLineup& init();
  
  public :

    StaticLineup();
    ~StaticLineup();
};

//---
inline System::StaticLineup& System::StaticLineup::init() {

  if (this->phases) delete [ ] this->phases;

  this->phases= NULL;
  
  return *this;
}
  
#endif  
