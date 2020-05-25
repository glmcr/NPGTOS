//-*-c++-*-

//---
#include "EoS/ThermoParams.hpp"
#include "EoS/ThermoParamsPerpleX.hpp"

//---
EoS::ThermoParams::ThermoParams() {
  this->init();
}

//---
EoS::ThermoParams::ThermoParams(BirchMurnaghanOrd3MethodT BMOrd3MethodType) {
  
  this->init();

  switch (BMOrd3MethodType) {

    case PERPLE_X_NEWTON :

      this->vdPBirchMurnaghanOrd3= vdPPerpleXBM3;
      break;

    // case BRUTE_FORCE :
    //   //this->vdPBirchMurnaghanOrd3= vdPBruteForceBM3;
    //   break; 
      
    default :

      std::cerr << "ERROR: " << __func__ <<
	           ": Invalid EoS BirchMurnaghanOrd3MethodT method -> " << BMOrd3MethodType << " !" << std::endl;
      std::exit(1);
  }
}

//---
EoS::ThermoParams::~ThermoParams() {
  this->init();
}

//---
EoS::ThermoParams& EoS::ThermoParams::setupRf(EoS::CrunchGaloreT WhichOne) {

  switch(WhichOne) {

    case PerpleX01 :
      
      ThermoParams::setupPerpleX01(*this);
      break;

    case PerpleX02 :

      ThermoParams::setupPerpleX02X04(*this);
      break;

    case PerpleX03 :

      //--- Nothing to doooo, nowhere to go(to), I wanna be sedated(The Ramones)
      break;

    case PerpleX04 :

      ThermoParams::setupPerpleX02X04(*this);
      break;      
      
    case PerpleX07 :
      
      ThermoParams::setupPerpleX07(*this);
      break;
      
    case PerpleX08 :
      
      ThermoParams::setupPerpleX08(*this);
      break;

    case PerpleX09 :
      
      ThermoParams::setupPerpleX09(*this);
      break;
      
    // case PerpleX11 :      
    //   ThermoParams::setupPerpleX11(*this);
    //   break;
      
    default :
      
      std::cerr << "ERROR: " << __func__ <<
	           ": Invalid EoS setup method -> " << WhichOne << " !" << std::endl;
      std::exit(1);
  }
  
  return *this;
}
