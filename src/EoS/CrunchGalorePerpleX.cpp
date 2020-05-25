//-*-c++-*-

//---
#include "EoS/ThermoParams.hpp"
#include "EoS/CrunchGalore.hpp"

//---
double EoS::ThermoParams::crunchPerpleX02X03X04(const ThermoParams& Tp, double Pressure, double Temperature) {

  //---  Perple_X gcpd sunbroutine:
  //
  // c                                 gottschalk.
  //        vdp = thermo(11,id)*dexp(thermo(13,id)*t)*
  //    *               (1d0 - dexp(thermo(18,id)*(p - pr)))

  //--- Set vdP as if we have the case -3.0 <= Tp.bcr[_8] < 0.0 : 
  
  double vdP= Tp.bcr[_1] * exp(Temperature*Tp.bcr[_3]) * (1.0 - exp( (Pressure-STDP)*Tp.bcr[_8] ));

  if (Tp.b8CondStuff == B8_ZERO ) {

    vdP= normalVdPPolynomial(Tp, Pressure, Temperature);
  
  } else if (Tp.b8CondStuff == B8_GTT_ZERO || Tp.b8CondStuff == B8_LTT_MIN3 ) {

// c                                 murnaghan EoS:
// c                                 int(alpha,T=Tr..T)
//          ialpha = (thermo(11,id) + thermo(12,id)*t)*t +
//      *            thermo(13,id)*dlog(t) + thermo(14,id)/t + 
//      *            thermo(15,id)*dsqrt(t) + thermo(23,id)  

    //--- Same iAlpha for both cases:
    
    const double iAlpha= Temperature * (Tp.bcr[_1] + Temperature * Tp.bcr[_2]) +
                           log(Temperature) * Tp.bcr[_3] + Tp.bcr[_4] / Temperature + STDT_SQR * Tp.bcr[_5] + Tp.bcr[_13];

    //--- approx alpha 
    // c                                 v(t,pr)
    //       False:     vt = thermo(3,id)*dexp(ialpha)
    // c                                 use hollad & powell's approximate form
    //       True:      vt = thermo(3,id)*(1d0 + ialpha)   

    //--- Default vT value for both conditional cases:
    double vT= exp(iAlpha) * Tp.volumeRf.getValue();
    
    // c  compute kt using Anderson-Gruneisen parameter
    // c  and expansivity ala Helffrich & Connolly 2009.
    // True: kt = thermo(16,id)*dexp(-thermo(21,id)*ialpha)
    // False: kt = thermo(16,id) + thermo(17,id)*t
    
    double kT= ( Tp.andersonGruneisen ? Tp.bcr[_6] * exp(-iAlpha*Tp.bcr[_11]) : Tp.bcr[_6] + Temperature * Tp.bcr[_7] );
    
    if (kT < 0.0) { 

      //--- Add WARNING log here about kT < 0.0 and
      //    that we have to de-equilibrate the phase ??

      //--- Destabilizing(de-equilibrate??) the phase
      vdP= PHASE_DESTAB_CONST * Pressure;   
      
    } else if (Tp.b8CondStuff == B8_GTT_ZERO ) {

      //--- b8 > 0.0 condition in Perple_X
      // use holland & powell's approximate alpha form
      
      vT= ( Tp.approxAlpha ? Tp.volumeRf.getValue() * (1.0 + iAlpha) : vT );

// c                                 Murnaghan EoS:
// c                                 vdp = V(1,T)*KT**(1/K')/(K'-1)
// c                                 * [(KT+K'*p)**(1-1/K') -
// c                                 (KT+K'*pr)**(1-1/K')]
//
//          vdp = vt * kt**(1d0/thermo(18,id))/thermo(22,id) 
//      *            *((kt+thermo(18,id)*p)**thermo(19,id) - (kt+thermo(20,id))**thermo(19,id))

      #ifdef _WTF
      assert( (int)ceil(fabs(Tp.bcr[_12])) >= 1);
      #endif	
      
      vdP= vT * ( pow( Pressure * (kT + Tp.bcr[_8]), Tp.bcr[_9] ) -
		  pow( (kT + Tp.bcr[_10]), Tp.bcr[_9]) ) * pow(kT, (1.0 / Tp.bcr[_8])) / Tp.bcr[_12];
      
    } else {

      //--- The other condtional possible : b8 < -3.0  

      if (Tp.b6CondStuff == B6_ZERO ) {
	
      //--- Perple_X comments: 
//          if (thermo(16,id).eq.0d0) then 
// c                                 assume ghiorso's expressions for v0 and k (KT)
// c                                 vt = Volume at 1 bar, T
//             vt = thermo(3,id) + thermo(11,id) * (t - trv)
//             kt = -vt / (thermo(12,id) + thermo(13,id) * (t - trv) )

        const double TDiffFactor= Temperature - GHIORSO_VT_CONST;
	
	vT= Tp.volumeRf.getValue() + TDiffFactor * Tp.bcr[_1] ;

	kT= -vT/( Tp.bcr[_2] + TDiffFactor * Tp.bcr[_3]);
      }

      if (vT < 0.0 || kT < 0.0 ) {

        //--- Add WARNING log here about vT < 0.0 or kT < 0.0 and
        //    that we have to de-equilibrate the phase ??

        //--- Destabilizing(de-equilibrate??) the phase
        vdP= PHASE_DESTAB_CONST * Pressure;   	 
	
      } else {

	//vdp = vdpbm3 (vt,kt,thermo(18,id))

	#ifdef _WTF
        assert( Tp.vdPBirchMurnaghanOrd3 );
        #endif

	vdP= Tp.vdPBirchMurnaghanOrd3(Pressure, vT, kT, Tp.bcr[_8]);
      }
    }
  }

  return vdP;
}

// //---
// double EoS::ThermoParams::crunchPerpleX11(const EoS::ThermoParams& Tp, double Pressure, double Temperature) {

//   double vdP= 0.0;

//   std::cerr << "ERROR: " << __func__ << " method: not ready yet !" << std::endl;
  
//   return vdP;
// }
