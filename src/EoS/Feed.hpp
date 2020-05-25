//-*-c++-*-
#ifndef _NPGTOSEoSFeed_hpp
#define _NPGTOSEoSFeed_hpp

//---
#include <cmath>

//--- <cstring> for memset and memcpy handy C utilities
#include <cstring>

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/ScalarQuantity.hpp"

//---
#include "EoS/EoS.hpp"
#include "EoS/ThermoConsts.hpp"
#include "EoS/ThermoParams.hpp"

//--- Need to include all EoS/CrunchGalore*.hpp files 
//    here otherwise  g++ shoots the classic "used but 
//    never defined" warning and also could not link 
//    the CrunchGalore* methods in the binary executable.
#include "EoS/CrunchGalore.hpp"
#include "EoS/CrunchGalorePerpleX.hpp"
#include "EoS/CrunchGaloreHub.hpp"

//--- Need to include EoS/CrunchGalore.hpp here otherwise 
//    g++ utters the classic "used but never defined" warning
//    and also could not link the CrunchGalore methods in
//    the binary executable.
//#include "EoS/CrunchGalore.hpp"

//---
class EoS::Feed final :
  private EoS::ThermoConsts,
    private EoS::ThermoParams {

  private :

  protected :        

    //--- TODO: Use a LambdaTransition inherited class instead ??
    int transitionType;
    double* transitionCoeffs;

    //---
    virtual inline Feed& initThermoParams(bool Hsc2Supcrt, const Core::StoichioComponent* const StCBundle) final;
    
    //--- 
    double (*getVdP) (const ThermoParams& Tp, double Pressure, double Temperature);
    
  public :

    Feed();
    Feed(CrunchGaloreT WhichCrunch);
    ~Feed();

    //---
    virtual inline Feed& init() final override;   
    
    //--- TODO: Could getHeatCapacity method  be moved to ThermoConsts class ??
    //virtual inline double getHeatCapacity(double Temperature) const final;
    
    virtual inline double crunch(double Pressure, double Temperature) const final;

    static inline double getHeatCapacity(double Temperature, const double* const CData);    
};

//---
inline double EoS::Feed::getHeatCapacity(double Temperature, const double* const CData) {

  #ifdef _WTF
  //--- It's really an error to have Temperature<EoS::STDT
  assert(Temperature< EoS::STDT);
  #endif

  //--- Perple_X : http://www.perplex.ethz.ch/perplex_thermodynamic_data_file.html
  //
  //    CP(T,Pr) = c1 + c2·T + c3/T2 + c4·T2 + c5/T1/2 + c6/T + c7/T3  + c8·T3

  const double TSQE= Temperature * Temperature;
  
  //--- Uncomment the following line when using more than 5 "c" coefficients:
  const double TCBE= Temperature * TSQE;

  return CData[_1] + CData[_2] * Temperature + CData[_3] / TSQE + CData[_4] * TSQE +
           CData[_5] / sqrt(Temperature) + CData[_6] / Temperature + CData[_7] / TCBE + CData[_8] * TCBE;  
}

//--- TODO: check for possible other heat capacity equations definitions ??
// inline double EoS::Feed::getHeatCapacity(double Temperature) const {

//   #ifdef _WTF
//   //--- It's really an error to have Temperature<EoS::STDT
//   assert(Temperature< STDT);
//   #endif

//   //--- Connolly : http://www.perplex.ethz.ch/perplex_thermodynamic_data_file.html
//   //
//   //    CP(T,Pr) = c1 + c2·T + c3/T2 + c4·T2 + c5/T1/2 + c6/T + c7/T3  + c8·T3

//   const double TSQE= Temperature * Temperature;
  
//   //--- Uncomment the following line when using more than 5 "c" coefficients:
//   const double TCBE= Temperature * TSQE;

//   return this->ccc[_1] + this->ccc[_2] * Temperature +
//            this->ccc[_3] / TSQE + this->ccc[_4] * TSQE +
//              this->ccc[_5] / sqrt(Temperature) + this->ccc[_6] / Temperature + this->ccc[_7] / TCBE + this->ccc[_8]*TCBE;
// }

//---
inline double EoS::Feed::crunch(double Pressure, double Temperature) const {

  #ifdef _WTF
  assert(Pressure>= EoS::STDP);    //Core::Constants::STD_PRESSURE.getValue();
  assert(Temperature>= EoS::STDT); //Core::Constants::STD_TEMPERATURE.getValue();
  assert(this->getVdP);
  #endif

  //--- return G(zero) - SdT + VdP ( - NdMu ??)
  //    NOTE1: this->getSdT() returns -SdT
  //    NOTE2: We could have used a polymorphic this->getVdP method here to
  //           apply the full-fledged OO paradigm but we would probably have
  //           had a performance penalty compared to this old-school-a-la-C
  //           static method pointer trick.
  
  return this->gibbsRf.getValue() +
           this->getSdT(Temperature) +
             this->getVdP(*this, Pressure, Temperature);
}

//---
inline EoS::Feed& EoS::Feed::init() {

  if (this->transitionCoeffs) delete this->transitionCoeffs;

  this->transitionCoeffs= NULL;

  this->transitionType= Core::UNDEFINED;
  
  this->getVdP= NULL;
  
  return *this;
}

//---
inline EoS::Feed& EoS::Feed::initThermoParams(bool Hsc2Supcrt,
					      const Core::StoichioComponent* const StCBundle) {

  #ifdef _WTF
  assert(StCBundle);
  #endif
  
  const int sqSize= sizeof(Core::ScalarQuantity);

  //--- Use of quick low level memcpy C
  //    function to do deep copies of objects
  //    without pointers attributes:
  memcpy(&this->gibbsRf, &this->stdGibbs, sqSize);
  memcpy(&this->volumeRf, &this->stdVolume, sqSize);
  memcpy(&this->entropyRf, &this->stdEntropy, sqSize);

  //memcpy(&this->enthalpyRf, &this->stdEnthalpy, sqSize);
  
  //--- NOTE: The web based doc of Perple_X is misleading here
  //          with the HSC to SUPCRT conversion for Gibbs
  //          reference data:
  //
  //          Instead of this -> G0HSC(T,P) - G0SUPCRT(T,P) =  Tr·Selements(Tr,Pr)
  //
  //          We should have that -> G0SUPCRT(T,P) - G0HSC(T,P) =  Tr·Selements(Tr,Pr)
  //
  //     The code is ok though :
// c                                 convert HSC G0 to SUP G0
//                         do j = 1, icomp
//                            thermo(1,k10) = thermo(1,k10) 
//      *                                   + tr*comp(ic(j))*sel(j)

  // //--- Check for possible HSC to SUPCRT conversion:
  // if (Hsc2Supcrt) {
  //   this->gibbsRf.setValue( this->gibbsRf.getValue() + STDT * );
  // }
  
  memcpy(&this->bcr[0], &this->bcc[0], BC_DIM*sizeof(double));
  memcpy(&this->ccr[0], &this->ccc[0], CC_DIM*sizeof(double));
  
  return *this;
}

#endif
