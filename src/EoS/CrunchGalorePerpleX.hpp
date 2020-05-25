//-*-c++-*-
#ifndef _NPGTOSEoSCrunchGalorePerpleX_hpp
#define _NPGTOSEosCrunchGalorePerpleX_hpp

//---
#include <cmath>

//---
#include "NPGTOS.hpp"
#include "EoS/EoS.hpp"

//--- Seems ok:
inline double EoS::ThermoParams::crunchPerpleX08(const ThermoParams& Tp, double Pressure, double Temperature) {

  #ifdef _WTF
  assert(Pressure>= EoS::STDP);   
  assert(Temperature>= EoS::STDT); 
  #endif
  
  // //--- Connolly http://www.perplex.ethz.ch/perplex_thermodynamic_data_file.html
  // //    Normal polynomial for Cp; Mie-Gruneisen Einstein oscillator
  // //    for thermal pressure; modified Tait for V (Holland & Powell, 2010)
  // //    Perple_X Eos n.8

  //--- Perple_X gcpd subroutine part:
  
  //pth = thermo(11,id) * ( 1d0/(dexp(thermo(15,id)/t) -1d0 ) -thermo(19,id))
  const double thermalPressure= Tp.bcr[_1] * ( 1.0/( exp(Tp.bcr[_5]/Temperature) - 1.0 ) - Tp.bcr[_9]);

  //   v1 = 1d0 + (p -pth)*thermo(17,id)
  //   v2 = 1d0 + (pr-pth)*thermo(17,id)

  const double v1Loc= 1.0 + (Pressure - thermalPressure) * Tp.bcr[_7];
  const double v2Loc= 1.0 + (STDP - thermalPressure) * Tp.bcr[_7];

  //--- Destabilizing(de-equilibrate??) the phase by default for possible
  //    cases where we have v1Loc < 0.0 OR v2Loc < 0.0
  double vdP= PHASE_DESTAB_CONST * Pressure;   

  //--- Both if evaluations should give the same bool results.
  //    Does negation of (v1Loc < 0.0 || v2Loc < 0.0) is really
  //    slower than direct (v1Loc >= 0.0 && v2Loc >= 0.0) ??
  //if (v1Loc >= 0.0 && v2Loc >= 0.0) {
  
  if ( !(v1Loc < 0.0 || v2Loc < 0.0) ) {   

    //--- 
    //c                                 int(vdp,p=Pr..Pf)
    //   vdp = (thermo(16,id)*( (v1**thermo(18,id) - v2**thermo(18,id)) / thermo(20,id)-p+pr) +p-pr) * thermo(3,id)

    const double pDiff= Pressure - STDP;

    //--- This is the VdP - NdMu(?) term of the EoS:
    vdP= Tp.volumeRf.getValue() *
            ( pDiff + Tp.bcr[_6] * ( (pow(v1Loc, Tp.bcr[_8] ) - pow(v2Loc, Tp.bcr[_8]) )/Tp.bcr[_10] - pDiff)); 
    
  } else {

    //--- print v1Loc < 0.0 || v2Loc < 0. warning on stdout here.
  }

  return vdP;
}

//--- Seems ok:
inline double EoS::ThermoParams::crunchPerpleX09(const EoS::ThermoParams& Tp, double Pressure, double Temperature) {

  //--- This EoS seems to be used only for gases. 
  
  #ifdef _WTF
  assert(Pressure>= EoS::STDP);   
  assert(Temperature>= EoS::STDT); 
  #endif
  
  //--- gcpd subroutine part:

  const double tDiff= Temperature - STDT; //--- STDT == Temperature reference state constant
  
  //  kt = thermo(16,id) + thermo(15,id) * (t-tr)
  const double ktLoc= Tp.bcr[_6] + Tp.bcr[_5] * tDiff;
  
  const double ktLocMb7= ktLoc * Tp.bcr[_7];
  
  //a = thermo(19,id)/( thermo(19,id)+ kt*thermo(17,id) )
  //b = thermo(18,id)/kt-thermo(21,id)
  //c = 1d0 - ( thermo(19,id)+kt*thermo(17,id) ) /( thermo(20,id) - kt*thermo(17,id) )

  const double aLoc= Tp.bcr[_9]/(Tp.bcr[_9] + ktLocMb7);
  const double bLoc= Tp.bcr[_8]/ktLoc - Tp.bcr[_11];
  const double cLoc= 1.0 - (Tp.bcr[_9] + ktLocMb7) / (Tp.bcr[_10] -  ktLocMb7);

  const double pDiff= Pressure - STDP; //--- STDP == Pressure reference state constant
  
// vdp = ( ( ( (p*b+1d0)**c-(Pr*b+1d0)**c)/b/c + pr-p)*a-pr+p ) * thermo(3,id) * dexp(thermo(11,id)*(t-tr))
// c                                 vt
//

  //--- V*dP
  return Tp.volumeRf.getValue() * tDiff * exp(Tp.bcr[_1]) * ( pDiff +
	   ( (pow(1.0 + Pressure*bLoc, cLoc) - pow(1.0 + STDP*bLoc, cLoc))/bLoc/cLoc - pDiff) * aLoc );
}

//--- Get rid of what follows ??
// //--- Still to be completed:
// inline double EoS::Feed::galore02(const EoS::Feed& Fd, double Pressure, double Temperature) {
//   // alphaIntegralE2E4(T,Pr)= -(b1*tr + (b2*tr*tr)/2 + b3*dlog(tr) - b4/tr + 2*b5*dsqrt(tr)) +
//   //                          b1 + (b2*T)/2 + b3/T - b4/T^2 + 2*b5/sqrt(T)
//   const double alphaIntegralE2E4= Fd.thermalExpCst + Fd.getIsobaricExpAlphaE2E4(Temperature);
//   //--- not done yet, still a work in progress !
//   return Fd.stpVolume.getValue(); // +  
// }

// //--- Still to be completed:
// inline double EoS::Feed::galore03(const EoS::Feed& Fd, double Pressure, double Temperature) {
//   //V(T,Pr) = V0 + b1·(T-1673)
//   const double TDiff= Temperature - EOS03_TCONST;
//   //const double VTPr= Fd.stpVolume.getValue() +Fd.b[_1]*Temperature - EOS03_TCONST;
//   //K(T,Pr) = V(T,Pr)/[b2 + b3·(T-1673)]
//   //--- Check denom value for near zero value here ??
//   const double KTPr= (Fd.stpVolume.getValue() + Fd.b[_1]*TDiff) / (Fd.b[_2] + Fd.b[_3]*TDiff);
//   double VTP= 0.0; 
//   //--- not done yet, still a work in progress !
//   return VTP; // +  
// }

// //--- Seems complete BUT see NOTE below:
// inline double EoS::Feed::galore07(const EoS::Feed& Fd, double Pressure, double Temperature) {
//   //--- Connolly : http://www.perplex.ethz.ch/perplex_thermodynamic_data_file.html
//   //
//   //  V(T,P) = V0·exp[b3·(T-Tr) + b8·(P-Pr)]
//   //
//   //  NOTE: This does not seem to be the same formulation as in the last version
//   //        of the Perple_X Fortran code !!!      
//   //--- VTP
//   return Fd.stpVolume.getValue() *
//            exp( Fd.b[_3] * (Temperature - EOS_TSTP) + Fd.b[_8]*(Pressure - EOS_PSTP));    
// }

// //--- Seems complete
// inline double EoS::Feed::galore13(const EoS::Feed& Fd, double Pressure, double Temperature) {

//   //--- Connolly : http://www.perplex.ethz.ch/perplex_thermodynamic_data_file.html
//   //
//   //  alphaIntegralE13(T,Pr)= -(b1*tr + (b2*tr*tr)/2 + b3*dlog(tr) - b4/tr) + b1 + b2·T + b3/T + b4/T2 
  
//   const double alphaIntegralE13= Fd.thermalExpCst + Fd.getIsobaricExpAlphaE13(Temperature);

//   // K(T,Pr) = 1/(b5 + b6·T + b7·T2 + b8·T3) 

//   const double tmpDenom= Fd.bTHC[_5] + Temperature *
//                            (Fd.bTHC[_6] + Temperature * Fd.bTHC[_7] +
// 			      Temperature * Temperature * Fd.THC[_8]) ;
  
//   const double KTPr= Pressure*(1.0/tmpDenom);

//   // K' = b9 + b10·(T-Tr)· ln(T/Tr)
//   const double KPrime= Fd.bTHC[_9] + Fd.bTHC[_10] * (Temperature - EOS_TSTP) * log(Temperature/EOS_TSTP);

//   const double PMKPrime= Pressure * KPrime;
  
//   // V(T,Pr) = V0·exp[integral(alpha(T,Pr),T=Tr..T)]
//   // V(T,P) = V(T,Pr)·[1 - K'·P/{ K'·P + K(T,Pr) } ]1/K' 

//   const double powArg= 1.0 - PMKPrime/(PMKPrime + KTPr);
    
//   //--- V(T,P)
//   return Fd.stpVolume.getValue() * exp(alphaIntegralE13) * pow( powArg, 1.0/KPrime);
// }

#endif
