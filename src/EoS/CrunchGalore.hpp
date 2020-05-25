//-*-c++-*-
#ifndef _NPGTOSEoSCrunchGalore_hpp
#define _NPGTOSEosCrunchGalore_hpp

//---
#include <cmath>

//---
#include "NPGTOS.hpp"
#include "EoS/EoS.hpp"

//---
inline double EoS::ThermoParams::normalVdPPolynomial(const EoS::ThermoParams& Tp, double Pressure, double Temperature) {

  //--- From Perple_X gcpd subroutine:
  //
  // c                                 normal polynomial:
  //         vdp =  p * (thermo(3,id) 
  //    *               + (thermo(17,id) * t + thermo(12,id)) * t
  //    *               + (thermo(16,id) * p + thermo(14,id)) * p)
  
  return Pressure * ( Tp.volumeRf.getValue() +
		      Pressure * ( Pressure * Tp.bcr[_6] + Tp.bcr[_4] ) + 
		      Temperature * ( Temperature * Tp.bcr[_7] + Tp.bcr[_2]) );
}

// //--- Using EoS::ThermoParams::normalVdPPolynomial directly in CrunchGaloreHub    
// inline double EoS::ThermoParams::crunchPerpleX01(const EoS::ThermoParams& Th, double Pressure, double Temperature) {
//   #ifdef _WTF
//   assert(Pressure>= EoS::STDP);   
//   assert(Temperature>= EoS::STDT); 
//   #endif
//   //--- Simple normal polynomial for VdP computation:
//   return EoS::ThermoParams::normalVdPPolynomial(Th, Pressure, Temperature);
// }

#endif
