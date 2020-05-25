//-*-c++-*-

//---
#include "EoS/ThermoParams.hpp"

//--- Perple_X Newton-Raphson polynomial root(s) finding for
//    Birch-Murnaghan 3rd order vdP term
double EoS::ThermoParams::vdPPerpleXBM3(double Pressure, double VolumeAtT,
					double BulkMod, double BulkModPrime) {
  
  //double vdP= 0.0;

  //--- Perple_X code :  
//        a0 = 0.375d0 * vt * k
//       a1 = -0.125d0 * vt**2 * k
//       c0 = (-28d0 -6d0 * kprime) * vt * a0
//       c1 = (12d0 + 3d0 * kprime) * vt**2 * a0
//       c2 = (16d0 + 3d0 * kprime) * a0
//       c3 = a1 * vt * (-196d0 - 42d0 * kprime)
//       c4 = a1 * (80d0 + 15d0 * kprime)
//       c5 = a1 * vt * (108d0 + 27d0 * kprime)
// c                                 use murnaghan guess for volume. GH, 6/23/16
// c                                 initial guess for volume:
//       dv = 1d0
//       v = vt * (1d0 - kprime*p/k)**(dv/kprime)
//       itic = 0  

  //const double bulkModPrime= this->bcr[_8]; //--- this->bcr[_8] == kprime

  double vdP= 0.0;
  
  const double bulkModPrimeM3= 3.0 * BulkModPrime;
  const double volumeAtTSqr= VolumeAtT * VolumeAtT;
  
  const double a0=  0.375 * VolumeAtT * BulkMod; 
  const double a1= -0.125 * volumeAtTSqr * BulkMod;
  
  const double c0= -a0 * VolumeAtT * ( BulkModPrime * 6.0 + 28.0) ;
  const double c1=  a0 * volumeAtTSqr * (bulkModPrimeM3 + 12.0);
  const double c2=  a0 * (bulkModPrimeM3 + 16.0);
  const double c3= -a1 * VolumeAtT * ( BulkModPrime * 42.0 + 196.0);
  const double c4=  a1 * (BulkModPrime * 15.0 + 80.0);
  const double c5=  a1 * VolumeAtT * ( BulkModPrime * 27.0 + 108.0);

  double volFuncDerivRatio= 1.0;
  double volIter= VolumeAtT * pow( (1.0 - BulkModPrime * Pressure / BulkMod), ( volFuncDerivRatio/ BulkModPrime ) );

  #ifdef _WTF
  assert(volIter> 0.0);
  #endif
  
  int iter= 0;
  
  //--- Newton-Raphson polynomial root(s) finding:  
  while( iter<= MAXNB_ITER_NEWTON_RAPHSON &&
	 volFuncDerivRatio> NEWTON_RAPHSON_CONV_THRESHOLD ) {

    // itic = itic + 1
    // rat = (vt/v)**r13
    // rat2 = rat**2
    // f = p  + ((c0*v*rat+c1+c2*v**2*rat2)/v**3)
    // df = (c3/rat2+c4*v/rat+c5)/v**4
    // dv = f/df
    // v = v - dv  
    
    const double volRatio= ONE_THIRD * (VolumeAtT / volIter);
    const double volRatioSqr= volRatio * volRatio;

    const double volIterSqr= volIter*volIter;

    #ifdef _WTF
    //--- Check for an epsilon instead ??
    assert( (int)ceil(fabs(volRatio)) >= 1);
    #endif    
    
    const double volFuncDeriv= (c3 / volRatioSqr + c4 * volIter / volRatio + c5) / (volIterSqr * volIterSqr);

    #ifdef _WTF
    //--- Check for an epsilon instead ??
    assert( (int)ceil(fabs(volFuncDeriv)) >= 1);
    #endif	    
    
    volFuncDerivRatio= ( ( Pressure + (c0 * volIter + c1 +
				       c2 * volIterSqr * volRatioSqr) ) / (volIter * volIterSqr) ) / volFuncDeriv; 
    volIter -= volFuncDerivRatio;
    
    iter++;
  }

  //--- Perple_X code :
// c                                 and the vdp integral is:
//       f = 0.5d0*((vt/v)**r23-1d0)
// c                                 checked in BM3_integration.mws
//       vdpbm3 = p*v - vt*(pr-4.5d0*k*f**2*(1d0-f*(4d0+kprime))) 

  //#ifdef _WTF
  //assert(volIter> 0.0 && volIter< MAX_VOLUME_CM3);
  //#endif

  if ( volIter< 0.0 || volIter> MAX_VOLUME_CM3) {

    vdP= PHASE_DESTAB_CONST * Pressure;
    
  } else { 
  
    const double vTTmp= ONE_HALF * ( pow( (VolumeAtT / volIter), TWO_THIRD) - 1.0 ); 
  
    //--- 
    vdP= Pressure * volIter - VolumeAtT * ( Pressure -
      4.5 * BulkMod * vTTmp * vTTmp* ( 1.0 - vTTmp * (4.0 + BulkModPrime)));
  }

  return vdP;  
}

//---
