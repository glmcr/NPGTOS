//-*-c++-*-
#ifndef _NPGTOSEoSThermoParamsPerpleX_hpp
#define _NPGTOSEosThermoParamsPerpleX_hpp

//--- for memset and memcpy handy C utilities
#include <cstring>

//---
#include "NPGTOS.hpp"
#include "EoS/EoS.hpp"

//--- NOTE: This file(ThermoParamsPerpleX.hpp) is included
//          by EoS/ThermoParams.cpp just after it includes EoS/ThermoParams.hpp
//#include "EoS/ThermoParams.hpp"

//---
inline EoS::ThermoParams& EoS::ThermoParams::setupPerpleX01(EoS::ThermoParams& Tp) {

  //--- Method used only at the init. stage of EoS::ThermoParams objects.
  //    ThermoParams objects are not supposed to be modified after being set once.
  //    (otherwise said: this method is only called once for each existing EoS::ThermoParams object)

  //const double STDT_INV
  
  //--- Perple_X conver subroutine part:  
// c                                G(P,T) polynomial forms, e.g., Helgeson et al 1978 (AJS)
// c                                Berman 1988 (J Pet).
//          g  = g
// c                                add the integral of sdt at tr,pr:
//      *       + s * tr - a * tr - b * tr * tr / 2d0 + c / tr
//      *       - d * tr**3 / 3d0 - 2d0 * e * dsqrt(tr)
//      *       - f * dlog(tr) + gg / tr / tr / 2d0 + f
//      *       + c8 / 4d0 * tr**4
// c                                add the constant components of the
// c                                integral -vdp at (t,pr):
//      *       - v * pr + b2 * tr * pr + b4 * pr * pr / 2d0
// c                                sign on b7 corrected June 16, 2004. PJ Gorman. 
//      *       - b6 * pr**3/3d0 - b7 * tr * tr * pr

  //--- Fortunately, the three following computations are only done once at the
  //    initialization stage (i.e. at the very beginning) of a run and only for the possible phases.
  
  Tp.gibbsRf.setValue(
			
    Tp.gibbsRf.getValue() + STDT * (Tp.entropyRf.getValue() - Tp.ccr[_1] -
      ONE_HALF * STDT * Tp.ccr[_2] - ONE_THIRD * STDT_SQE * Tp.ccr[_4]) + STDT_INV *
        Tp.ccr[_3] - 2.0 * STDT_SQR * Tp.ccr[_5] - STDT_LNE * Tp.ccr[_6] + ONE_HALF *
          STDT_INV * STDT_INV * Tp.ccr[_7] + Tp.ccr[_6] + ONE_QUARTER * STDT_SQE * STDT_SQE *
            Tp.ccr[_8] - STDP * (Tp.volumeRf.getValue() + STDT * Tp.bcr[_2] + ONE_HALF * STDP_SQE *
	      Tp.bcr[_4] - ONE_THIRD * STDP_SQE * Tp.bcr[_6] ) - STDP * STDT_SQE * Tp.bcr[_7]
  );

  
// c                                S* (T)
//          s  = a - b2*pr - s + a*dlog(tr) + b*tr - c/tr/tr/2d0
//      *        + d * tr * tr / 2d0 - 2d0 * e / dsqrt(tr) - f/tr
//      *        - gg / tr**3 / 3d0 + c8 * tr**3 /3d0
// c                                b7 term added June 16, 2004. PJ Gorman.
//      *        + b7 * 2d0 * pr * tr

  Tp.entropyRf.setValue(
			  
    -Tp.entropyRf.getValue() + Tp.ccr[_1] - STDP * Tp.bcr[_2] +
       STDT_LNE * Tp.ccr[_1] + STDT * Tp.ccr[_2] - ONE_HALF * STDT_INV *
         STDT_INV * Tp.ccr[_3] + ONE_HALF * STDT_SQE * Tp.ccr[_4] - 2.0 *
           Tp.ccr[_5]/STDT_SQR - STDT_INV * Tp.ccr[_6] - ONE_THIRD* STDT_INV *
             STDT_INV * STDT_INV * Tp.ccr[_7] +  ONE_THIRD * STDT * STDT_SQE * Tp.ccr[_8] + 2.0 * STDP * STDT * Tp.bcr[_7]
  );
  
// c                                V* (P)
//          v  = v - b2 * tr - b4 * pr  
// c                                b6 term added June 16, 2004. PJ Gorman.
//      *          + b6 * pr * pr
// c                                sign on b7 corrected June 16, 2004. PJ Gorman.
//      *          + b7 * tr * tr

  Tp.volumeRf.setValue( Tp.volumeRf.getValue() - STDT * Tp.bcr[_2] - STDP *
			  Tp.bcr[_4] + STDP_SQE * Tp.bcr[_6] + STDT_SQE * Tp.bcr[_7] );
    
// c                                a*  (-T log T)
// c        a  = a
// c                                b*  (-T*T)
//          b  = b7 * pr + b / 2d0
  Tp.ccr[_2]= STDP * Tp.bcr[_7] + ONE_HALF * Tp.ccr[_2]; 
      
// c                                c*  (-1/T)
//          c  = c / 2d0
  Tp.ccr[_3]= ONE_HALF * Tp.ccr[_3];
      
// c                                d*  (-T**3)
//          d  = d / 6d0
  Tp.ccr[_4]= ONE_HALF * ONE_THIRD * Tp.ccr[_4];
      
// c                                e*  (sqrt T)
//          e  = 4d0 * e
  Tp.ccr[_5]= 4.0 * Tp.ccr[_5];
      
// c                                f*  (log T)
// c        f  = f
// c                                gg* (-1/T**2)
//          gg = gg/6d0
  Tp.ccr[_7]= ONE_HALF * ONE_THIRD * Tp.ccr[_7];
      
// c                                c8* T**4
//          c8 = c8/12d0
  Tp.ccr[_8]= ONE_HALF * ONE_HALF * ONE_THIRD * Tp.ccr[_8];
      
// c                                b2* (PT)
//          b2 = b2
// c                                b7 term added June 16, 2004. PJ Gorman.
//      *          - 2d0 * b7 * tr
  Tp.bcr[_2]= Tp.bcr[_2] = 2.0 * STDT * Tp.bcr[_7];
    
// c                                b3* ((P-Pr) exp (T / c1))
// c        b3 = b3
// c                                b4* (P**2)
//          b4 = b4/2d0
// c                                b6 term added June 16, 2004. PJ Gorman.
//      *          - b6 * pr
  Tp.bcr[_4]= ONE_HALF * Tp.bcr[_4] - STDP * Tp.bcr[_6];
    
// c                                b5* (exp (P/ c2))
// c        b5 = c2 * b5
// c                                b6* (P**3)
//          b6 = b6/3d0
  Tp.bcr[_6] *= ONE_THIRD;
    
// c                                b7* (P*T**2)
// c        b7 = b7
  
  return Tp;
}

//---
inline EoS::ThermoParams& EoS::ThermoParams::setupPerpleX02X04(EoS::ThermoParams& Tp) {
  
//--- Perple_X conver subroutine:
//
//   else if (b8.ne.0d0) then
//  c                                 All remaining forms (ieos = 2, 4, >100) assume:
// c                                 1) alpha = b1 + b2*T + b3/T + b4/T^2 + b5/sqrt(T)
// c                                    which is reformulated here to 
// c                                    int(alpha,T=Tr..Tf) = b13 + b1*T + b2*T^2 + b3*ln(T) + b4/T + b5*sqrt(T)
//          b2 = b2/2d0 
//          b4 = -b4 
//          b5 = 2d0*b5
//          b13 = -(b1*tr + b2*tr*tr + b3*dlog(tr) + b4/tr + b5*dsqrt(tr))

  if (Tp.b8CondStuff != B8_ZERO) {
  
    Tp.bcr[_2] *= ONE_HALF;
    Tp.bcr[_4] *= -1.0;
    Tp.bcr[_5] *= 2.0;

    Tp.bcr[_13]= -STDT * Tp.bcr[_1] - STDT_SQE * Tp.bcr[_2] -
                  STDT_LNE * Tp.bcr[_3] - STDT_INV * Tp.bcr[_4] - STDT_SQR * Tp.bcr[_5];   

    //--- NOTE: The b6 assignment in the Perple_X code comments are not
    //          consequent with its real uncommented code assignment which
    //          i think should be
    //
    //          K = b6 - b7*Tr
    //
    //          instead of
    //
    //          K = b6 + b7*T
    //          
  // c                                 old parameter test forms:
// c                                 2) if lopt(4) not true, then the isothermal bulk modulus is
// c                                    K = b6 + b7*(T-Tr)
// c                                    which is reformulated to 
// c                                    K = b6 + b7*T
//
// actual code         if (.not.lopt(4)) b6 = b6 - b7*tr

    if ( !Tp.andersonGruneisen ) {

      Tp.bcr[_6]= Tp.bcr[_6] - STDT * Tp.bcr[_7];

      Tp.b6CondStuff == B6_NOT_ZERO;	 
    }
    
// c                                 operation solving constants for the Murnaghan (ieos=2), these are not
// c                                 used for the BM3.
//          b9 = (1d0-1d0/b8) 
//          b10 = b8*pr 
//          b12 = b8 - 1d0

    #ifdef _WTF
    //--- Validate this check on Tp.bcr[_8] different from 0.0. 
    assert( (int)ceil(fabs(Tp.bcr[_8])) >= 1);
    #endif
    
    Tp.bcr[_9]= 1.0 - 1.0/Tp.bcr[_8]; 

    Tp.bcr[_10]= STDP * Tp.bcr[_8];

    Tp.bcr[_12]= Tp.bcr[_8] - 1.0;

    //--- TODO: Check for EoSs > 300 ???
    
// c                                 anderson-gruneisen parameter is assumed = K' (abs(b8)) except for
// c                                 special EoS forms           
//          if (ieos.gt.300) then 
//             b11 = -s
//          else 
// c                                 special EoS, anderson-gruneisen stored in 
// c                                 s-position. 
//             b11 = dabs(b8) 
//          end if   

    Tp.bcr[_11]= fabs(Tp.bcr[_8]);
  }

  return Tp;  
}

//---
inline EoS::ThermoParams& EoS::ThermoParams::setupPerpleX07(EoS::ThermoParams& Tp) {

 //--- Perple_X conver subroutine:
 //
 //  c                                 exponential polynomial on volume, e.g., Haas et al 1986,
 //  c                                 Gottschalk 1997. b3 = alpha, -b8 = beta: 
 //          b1 = -v / b8 / dexp (b3*tr)

  Tp.bcr[_1]= -Tp.volumeRf.getValue() / Tp.bcr[_1] / exp(STDT * Tp.bcr[_3]) ;

  return Tp;
}

//---
inline EoS::ThermoParams& EoS::ThermoParams::setupPerpleX08(EoS::ThermoParams& Tp) {

  #ifdef _WTF
  assert(EoS::STDT>0.0);
  //--- Use a constant small epsilon to check for
  //    values dangerously close to 0.0 ???
  //assert(Tp.bcr[_5]>0.0);
  #endif
  
  //--- Method used only at the init. stage of EoS::ThermoParams objects.
  //    ThermoParams objects are not supposed to be modified after being set once.
  //    (otherwise said: this method is only called once for each existing EoS::ThermoParams object)
  
  //--- Connolly http://www.perplex.ethz.ch/perplex_thermodynamic_data_file.html
  //    Normal polynomial for Cp; Mie-Gruneisen Einstein oscillator
  //    for thermal pressure; modified Tait for V (Holland & Powell, 2010)
  //    Perple_X Eos n.8

  //--- Perple_X conver subroutine part:
// c                                 HP 2010 Full Tait EoS
// c                                 on input b1=alpha0, b5=theta, b6=k0, b7=k", b8=k'
// c                                 thermal pressure coefficients:
// c                                 alpha0/k0/xi0*theta -> b1
 
  //--- Avoid computing the same thing more than once: 
  const double expb5OnTr= exp(Tp.bcr[_5]/STDT);
  const double expb5OnTrM1= expb5OnTr - 1.0;

  //--- b1 = 1d0/b5 * b1 * b6 * tr**2 / dexp(b5/tr) * (dexp(b5/tr)-1d0)**2
  Tp.bcr[_1]= Tp.bcr[_1] * Tp.bcr[_6] *
                 expb5OnTrM1 * expb5OnTrM1 * (1.0/Tp.bcr[_5]) * (STDT_SQE/expb5OnTr) ;

  //--- b9= 1d0/(dexp(b5/tr)-1d0)
  Tp.bcr[_9]= 1.0/expb5OnTrM1;

  //--- Avoid computing the same thing more than once:
  const double onePb8= 1.0 + Tp.bcr[_8];
  const double b6Mb7= Tp.bcr[_6] * Tp.bcr[_7];					    
  const double c1LocDenom= (onePb8 + b6Mb7);

  //c                                 Tait a parameter -> b6
  //--- c1= (1d0+b8)/(1d0+b8+b6*b7)
  const double c1Loc= onePb8/c1LocDenom; 

  //c                                 Tait b parameter -> b7
  //--- c2 = b8/b6 - b7/(1d0+b8)
  const double c2Loc= Tp.bcr[_8]/Tp.bcr[_6] - Tp.bcr[_7]/onePb8;

  //c                                 Tait c parameter -> b8 = 1-c
  //--- b8= 1d0 - (1d0+b8+b6*b7)/(b8**2+b8-b6*b7)
  Tp.bcr[_8]= 1.0 - c1LocDenom/(Tp.bcr[_8]*Tp.bcr[_8] + Tp.bcr[_8] - b6Mb7);

  //--- b7 = c2
  //    b6 = c1

  Tp.bcr[_6]= c1Loc;
  Tp.bcr[_7]= c2Loc; 
   
  //--- b10 = b7*b8
  Tp.bcr[_10]= Tp.bcr[_7] * Tp.bcr[_8];  //c1Loc*c2Loc;

  //--- end conver subroutine part,
  
  return Tp;
}

//---
inline EoS::ThermoParams& EoS::ThermoParams::setupPerpleX09(EoS::ThermoParams& Tp) {

  #ifdef _WTF
  //--- Use a constant small epsilon to check for
  //    values dangerously close to 0.0 ???
  //assert(Tp.bcr[_9]!=0.0);
  #endif
  
  //--- Method used only at the init. stage of EoS::ThermoParams objects.
  //    ThermoParams objects are not supposed to be modified after being set once.
  //    (otherwise said: this method is only called once for each existing EoS::ThermoParams object)
  
  //--- Perple_X conver subroutine part:
  //c                                 True tait used for melt endmembers
  //c                                 kt = b6 + b5*(T-Tr)
  //c                                 vt = v0*exp(b1*(T-Tr))
  //          b9 = 1d0 + b8
  //          b10 = b8*b9
  //          b11 = b7/b9

  Tp.bcr[_9]= 1.0 + Tp.bcr[_8];
  Tp.bcr[_10]= Tp.bcr[_9] * Tp.bcr[_8];
  Tp.bcr[_11]= Tp.bcr[_7] / Tp.bcr[_9] ;
  
  return Tp;
}

//---
inline EoS::ThermoParams& EoS::ThermoParams::setupPerpleX11(EoS::ThermoParams& Tp) {

//  c                                Mie-Gruneisen Stixrude liquid Model:
// c                                G0 = F0 
// c                                S0 = S0 => S0 - Cv  
// c                                V0 = V0   
// c                                a  = Cv  
// c                                b  = K0 => 4.5d0*K0*V0  
// c                                c  = K0' => 4.5d0*K0*V0*(K'-4)    
// c                                d  = y0 => y0 - y'   
// c                                e  = y'    
// c                                f  = T0
// c                                --- dependent ---
// c                                gg = (S0-Cv-Cv*y0)*T0
// c                                b1 = Cv*(y0+ln(T0))-S0+Cv
// c                                b2 = ln(v0)
         // gg = (s - a - a*d)*f
         // b1 = a*(d+dlog(f)) - s + a
         // b2 = dlog(v)

         // s = s - a
         // b = 4.5d0*b*v
         // c = b*(c-4d0)
         // d = d - e

  const double volumeRf= Tp.volumeRf.getValue();
  const double entropyRf= Tp.entropyRf.getValue();
  
  //---            f             s          a             a              d
  Tp.ccr[_7]= Tp.ccr[_6] * ( entropyRf - Tp.ccr[_1] - Tp.ccr[_1] * Tp.ccr[_4] ); 
  Tp.bcr[_1]= Tp.ccr[_1] * ( Tp.ccr[_4] + log(Tp.ccr[_6]) ) - entropyRf + Tp.ccr[_1];
  Tp.bcr[_2]= log(volumeRf);

  //--- NOTE: Tp.entropyRf value modified here:
  Tp.entropyRf.setValue(entropyRf - Tp.ccr[_1]);

  Tp.ccr[_2]= 4.5 * Tp.ccr[_2] * volumeRf;
  Tp.ccr[_3]= Tp.ccr[_2] * ( Tp.ccr[_3] - 4.0 );
  
  Tp.ccr[_4] -= Tp.ccr[_5];
    
  return Tp;
}

#endif
