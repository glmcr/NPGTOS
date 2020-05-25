//-*-c++-*-
#ifndef _NPGTOSEoSThermoConsts_hpp
#define _NPGTOSEosThermoConsts_hpp

//--- for memset handy C utility
#include <cstring>

//---
#include "NPGTOS.hpp"
#include "EoS/EoS.hpp"
#include "Core/Constants.hpp"
#include "Core/ScalarQuantity.hpp"

//---
//using namespace NPGTOS;

//--- To hold all the EoS input data as it is.
//    (i.e. not supposed to be modified after being set)

class EoS::ThermoConsts {

  private :

  protected :

    //--- Perple_X EoSs 2,4 & 13
    //double thermalExpCst;
  
    Core::ScalarQuantity stdGibbs;    //--- Perple_X thermo1 param. (but constant here)
    Core::ScalarQuantity stdVolume;   //--- Perple_X thermo3 param. (but constant here)
    Core::ScalarQuantity stdEntropy;  //--- Perple_X thermo2 param. (but constant here)
    Core::ScalarQuantity stdEnthalpy; //---

    //--- Perple_X thermo11 to thermo22 (also b1,...,b12) coefficients
    //    BEFORE modifications done in conver subroutine.
    double bcc[BC_DIM]; 

    //--- Perple_X thermo4 to thermo10 AND thermo24 (also c1,...,c7,c8) coefficients
    //    BEFORE modifications done in conver subroutine.
    double ccc[CC_DIM]; //--- Almost got cccp here !!

    //--- TODO: Check for using a dynamic mcc array
    //          instead since the mcc coefficients
    //          are defined for some few other input
    //          databases other than Holland&Powell one.
    //          Perple_X m coefficients (the materials moduli ??)
    double mcc[MC_DIM]; 
  
    //---
    virtual inline ThermoConsts& init();

  //virtual inline Constants& setThermalExpCst(EoST WhichOne) final;
    
  public :

    ThermoConsts();
    //ThermoConsts(GaloreT WhichOne);
    ~ThermoConsts();
};

//---
inline EoS::ThermoConsts& EoS::ThermoConsts::init() {

  this->stdGibbs.set(0.0, 0.0, Core::UnitsT::UNDEFINED);
  this->stdVolume.set(0.0, 0.0, Core::UnitsT::UNDEFINED);
  this->stdEntropy.set(0.0, 0.0, Core::UnitsT::UNDEFINED);
  this->stdEnthalpy.set(0.0, 0.0, Core::UnitsT::UNDEFINED);
  
  memset(&this->bcc[0], 0x0, BC_DIM*sizeof(double));
  memset(&this->ccc[0], 0x0, CC_DIM*sizeof(double));
  memset(&this->mcc[0], 0x0, MC_DIM*sizeof(double));

  //this->thermalExpCst= 0.0;
  
  return *this;
}

#endif
