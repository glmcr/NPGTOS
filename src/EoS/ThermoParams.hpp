//-*-c++-*-
#ifndef _NPGTOSEoSThermoParams_hpp
#define _NPGTOSEosThermoParams_hpp

//--- <cstring> for memset and memcpy
//    old-schoolish handy C utilities.
#include <cstring>

//--- <cassert> for debugging.
#include <cassert>

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/ScalarQuantity.hpp"

//---
#include "EoS/EoS.hpp"

//---
class EoS::ThermoParams {

  private :

  protected :

    bool approxAlpha;
    bool andersonGruneisen;

    //#ifdef _USE_PERPLE_X
    PerpleXConditionalT b6CondStuff;
    PerpleXConditionalT b8CondStuff;
    //#endif
  
    //--- gibbsRf: Equivalent of Perple_X thermo(1,id) variable.
    //             N.B.: But only after modifications
    //             done (Ex. in EoS1 context) or not done
    //             (Ex. In most of the EoSs) in the
    //             conver subroutine.
    //double gibbsRf;
    Core::ScalarQuantity gibbsRf;
   
    //--- volumeRf: Equivalent of Perple_X thermo(3,id) variable. 
    //              The N.B. of gibbsRf also applies to it.
    //double volumeRf;
    Core::ScalarQuantity volumeRf;
  
    //--- entropyRf: Equivalent of Perple_X thermo(2,id) variable. 
    //               The N.B. of gibbsRf also applies to it.  
    //double entropyRf;
    Core::ScalarQuantity entropyRf;
  
    //--- enthalpyRf 
    //double enthalpyRf;
    //Core::ScalarQuantity enthalpyRf;
  
    //--- Equivalent of Perple_X thermo11 to thermo22 (also b1,...,b12) coefficients
    //    but after modifications done in the conver subroutine. 
    double bcr[BC_DIM];

    //--- Equivalent of Perple_X thermo4 to thermo10 AND thermo24 (also c1,...,c7,c8) coefficients
    //    but after modifications done in the conver subroutine.
    double ccr[CC_DIM]; //--- ccr: Not to be confused with the Creedence Clearwater Revival.

    inline ThermoParams& init();

    virtual ThermoParams& setupRf(EoS::CrunchGaloreT WhichOne) final;

    virtual inline double getSdT(double Temperature) const final;
  
    double (*vdPBirchMurnaghanOrd3) (double Pressure, double VolumeAtT, double BulkMod, double BulkModPrime);

    //--- thermo params setup methods
    static inline ThermoParams& setupPerpleX01(ThermoParams& Tp) ;
    static inline ThermoParams& setupPerpleX07(ThermoParams& Tp) ;
    static inline ThermoParams& setupPerpleX08(ThermoParams& Tp) ;
    static inline ThermoParams& setupPerpleX09(ThermoParams& Tp) ;
    static inline ThermoParams& setupPerpleX11(ThermoParams& Tp) ;
  
    static inline ThermoParams& setupPerpleX02X04(ThermoParams& Tp) ;

    static double vdPPerpleXBM3(double Pressure, double VolumeAtT, double BulkMod, double BulkModPrime);
  
  public :

    ThermoParams();
    ThermoParams(BirchMurnaghanOrd3MethodT BMOrd3MethodType);
    ~ThermoParams();

    //static inline double perpleXb8Conditionals(const EoS::ThermoParams& Th, double Pressure, double Temperature);
  
    //--- TODO: Implement EoS13
    //virtual inline double getIsobaricExpAlphaE13(double Temperature) const final;
    //virtual inline double getIsobaricExpAlphaE2E4(double Temperature) const final;  

    //double (*vdPBirchMurnaghanOrd3) (double Pressure, double VT, double KT, double BulkModPrime);

    //static double crunchPerpleX11(const ThermoParams& Tp, double Pressure, double Temperature);  
    static double crunchPerpleX02X03X04(const ThermoParams& Tp, double Pressure, double Temperature);
  
    static inline double crunchPerpleX03(const ThermoParams& Tp, double Pressure, double Temperature);  
    static inline double crunchPerpleX07(const ThermoParams& Tp, double Pressure, double Temperature);
    static inline double crunchPerpleX08(const ThermoParams& Tp, double Pressure, double Temperature);
    static inline double crunchPerpleX09(const ThermoParams& Tp, double Pressure, double Temperature);
  
    static inline double normalVdPPolynomial(const EoS::ThermoParams& Tp, double Pressure, double Temperature);

  //static double vdPPerpleXBM3(double Pressure, double VolumeAtT, double BulkMod, double BulkModPrime);
};

//---
inline double EoS::ThermoParams::getSdT(double Temperature) const {

  #ifdef _WTF
  //--- It's really an error to have Temperature<EoS::STDT
  assert(Temperature>= EoS::STDT);
  #endif
  
  //--- It returns -SdT to be precise so it has to be added by the calling method.
  
  //--- Perple_X gcpd subroutine:
  //
  //       gval = thermo(1,id)
  // c                                 -sdt
  //      *      + t * ( thermo(2,id) - thermo(4,id) * dlog(t)
  //             - t * (thermo(5,id) + (thermo(7,id) - thermo(24,id)*t) * t) )
  //      *      - (thermo(6,id) + thermo(10,id) / t) / t
  //      *      + thermo(8,id) * dsqrt(t) + thermo(9,id)*dlog(t)

  //--- Avoid computing the same thing more than once:
  const double LNET= log(Temperature);
  const double TINV= 1.0/Temperature;

  //--- tinv= 1/t
  // (thermo(6,id) + thermo(10,id) / t) / t == (thermo(6,id) + thermo(10,id)*tinv)*tinv
  //  multiplications are better for optimization than divisions
  
  return Temperature * ( this->entropyRf.getValue() * LNET * this->ccr[_1] -
	   Temperature * ( this->ccr[_2] + Temperature * ( this->ccr[_4] - Temperature * this->ccr[_8])) ) -
             (this->ccr[_4] + this->ccr[_7] * TINV) * TINV + sqrt(Temperature) * this->ccr[_4] + LNET * this->ccr[_6];
}

//---
inline EoS::ThermoParams& EoS::ThermoParams::init() {

  this->approxAlpha= true;
  this->andersonGruneisen= false;

  this->b6CondStuff= PerpleXConditionalT::B6_ZERO;
  this->b8CondStuff= PerpleXConditionalT::B8_ZERO;
  
  // this->gibbsRf=
  //   this->volumeRf=
  //     this->entropyRf= 0.0;
  //     //this->enthalpyRf= 0.0;

  this->gibbsRf.set(0.0, 0.0, Core::UnitsT::UNDEFINED);
  this->volumeRf.set(0.0, 0.0, Core::UnitsT::UNDEFINED);
  this->entropyRf.set(0.0, 0.0, Core::UnitsT::UNDEFINED);

  memset(&this->bcr[0], 0x0, BC_DIM*sizeof(double));
  memset(&this->ccr[0], 0x0, CC_DIM*sizeof(double));

  this->vdPBirchMurnaghanOrd3= NULL;
  
  return *this;  
}

// //---
// inline double EoS::Feed::getIsobaricExpAlphaE13(double Temperature) const {

//   // #ifdef _WTF
//   // assert(Temperature>0);
//   // #endif
  
//   //--- Connolly : http://www.perplex.ethz.ch/perplex_thermodynamic_data_file.html
//   //
//   //   Non-constant part of integral(alpha,T=Tr..Tf) = b1*T + b2*T^2 + b3*ln(T) + b4/T
//   //    

//   return Temperature*(this->bTHC[_1] + 0.5*Temperature*this->bTHC[_2]) +
//             log(Temperature)*this->bTHC[_3] + this->bTHC[_4]/Temperature; 
// }

// //---
// inline double EoS::Feed::getIsobaricExpAlphaE2E4(double Temperature) const {

//   // #ifdef _WTF
//   // assert(Temperature>0);
//   // #endif
  
//   //--- Connolly : http://www.perplex.ethz.ch/perplex_thermodynamic_data_file.html
//   //
//   //  Non-constant part of integral(alpha,T=Tr..Tf) = b1*T + b2*T^2 + b3*ln(T) + b4/T + b5*sqrt(T)
  
//   return this->getIsobaricExpAlphaE13(Temperature) + this->bTHC[_5]/sqrt(Temperature);
// }


#endif
