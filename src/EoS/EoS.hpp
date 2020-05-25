//-*-c++-*-
#ifndef _NPGTOSEoS_hpp
#define _NPGTOSEoS_hpp

//---
#include <cmath>

//---
#include "NPGTOS.hpp"
#include "Core/Constants.hpp"

//---
namespace NPGTOS {

  namespace EoS {

    //--- TODO: Create a specific PerpleX namespace ??
    //          Will see if it becomes too large in terms
    //          of source files.

    typedef enum {
                   PERPLE_X_NEWTON //,
                   // BRUTE_FORCE
		    
                 } BirchMurnaghanOrd3MethodT;
    
    typedef enum {
                   B8_ZERO,     //--- b8 == 0
		   B8_GTT_ZERO, //--- b8 > 0.0
                   B8_LTT_MIN3,  //--- b8 < -3.0
                   //BTW_MINUS3_ZERO  //--- -3.0 <= b8 < 0.0
                   B6_ZERO,
		   B6_NOT_ZERO
		   
                 } PerpleXConditionalT;    

    //--- Not limited to Perple_X EoSs
    //    we can add new EoSs at will
    //    (But only after rigorous tests
    //     and validation obviously)
    typedef enum {
                   PerpleX01, //--- EoS 1 in Perple_X.
		   PerpleX02, //--- EoS 2 in Perple_X.
		   PerpleX03, //--- EoS 3 in Perple_X.
		   PerpleX04, //--- EoS 4 in Perple_X.
		   PerpleX07, //--- EoS 7 in Perple_X.
                   PerpleX08, //--- EoS 8 in Perple_X, seems only used with Holland&Powell input data.
                   PerpleX09  //--- EoS 9 in Perple_X, seems only used with Holland&Powell input data.
		   //PerpleX11  //--- EoS 11 in Perple_X, Mie-Gruneisen Stixrude liquid Model:
		   
                 } CrunchGaloreT;

    //--- For rigorous tests and validation:
    // typedef enum {
    // } CrunchGaloreTestsT;
    
    //--- Always update GALORE_DIM with the last item in CrunchGaloreT enum:
    static const int CRUNCH_GALORE_DIM= PerpleX09+1; 
    
    static const double PHASE_DESTAB_CONST= 1.0e12; //--- 1.0e12 == pow(10,12);
    
    static const double GHIORSO_VT_CONST= 1673.15; 

    static const int MAXNB_ITER_NEWTON_RAPHSON= 20;
    
    static const double MAX_VOLUME_CM3= 1.0e6; //-- 1m3 in cm3
    static const double NEWTON_RAPHSON_CONV_THRESHOLD= 1.0e-05; //--- pow(10,-5)

    
    //--- Constants shortcuts to STD Pressure and Temperature
    static const double STDP= Core::Constants::STD_PRESSURE.getValue();
    static const double STDT= Core::Constants::STD_TEMPERATURE.getValue();

    //--- Define STDP and STDT derived constants OAFA(Once-And-For-All) for all EoSs:
    static const double STDP_SQE= STDP*STDP;

    static const double STDT_LNE= log(STDT);
    static const double STDT_INV= 1.0/STDT;
    static const double STDT_SQE= STDT*STDT;
    
    static const double STDT_SQR= sqrt(STDT);
    //static const double STDT_SQR_INV= 1.0/STDT_SQR;

    static const double ONE_HALF= 1.0/2.0; 
    static const double ONE_THIRD= 1.0/3.0;
    static const double ONE_QUARTER= 1.0/4.0;
    static const double TWO_THIRD= 2.0/3.0;
    
    //--- Corresponding C array mapping:
    //              0   1   2   3   4   5   6   7   8    9   10   11  12
    typedef enum { _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13 } BCMMapT;

    //--- Always set BC_DIM to the last item in BCMMapT
    //    Otherwise we end up with awkward segfault SNAFUs.
    static const int BC_DIM= _13+1;
    
    static const int MC_DIM=  _3+1; 
    static const int CC_DIM=  _8+1; 
    
    //--- Forward declaration of EoS classes:
    class Feed;
    class ThermoConsts;
    class ThermoParams;
    
  };
};

#endif
