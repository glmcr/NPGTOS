//-*-c++-*-

//---
#include "EoS/Feed.hpp"

//---
EoS::Feed::Feed() :
  EoS::ThermoConsts::ThermoConsts(),
    EoS::ThermoParams::ThermoParams(){

  this->init();
}

//--- Here pass either a JSON objects map to
//    EoS::Feed::Feed contructor and cascade the
//    this map to EoS::ThermoConsts::ThermoConsts
//    to initialize it as it should be;
EoS::Feed::Feed(EoS::CrunchGaloreT WhichEoS) :
  EoS::ThermoConsts::ThermoConsts(), EoS::ThermoParams::ThermoParams() {

  this->init();

  #ifdef _WTF
  assert(0 <= WhichEoS && WhichEoS < EoS::CRUNCH_GALORE_DIM);
  #endif

  //--- EoS::ThermoConsts::ThermoConsts() must have been
  //    initialized at this point before using this->initThermoParams.setup(WhichEoS);
  //this->setRfParams(WhichEoS);

  //this->initThermoParams().setupRf(WhichEoS);
  
  //--- Set the this->getVdP EoS method pointer to
  //    the proper one according to the WhichOne argument:
  this->getVdP= EoS::CrunchGaloreHub[WhichEoS];

  #ifdef _WTF
  assert(this->getVdP);
  #endif
}

//---
EoS::Feed::~Feed() {

  this->ThermoConsts::~ThermoConsts();
  
  this->init();
  
  //if (this->transitions) delete this->transitions;
  //this->transitions= NULL;
}
