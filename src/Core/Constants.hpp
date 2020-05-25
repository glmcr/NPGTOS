//-*-c++-*-
#ifndef _NPGTOSCoreConstants_hpp
#define _NPGTOSCoreConstants_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/ScalarQuantity.hpp"

//---
namespace NPGTOS {

  namespace Core {

    namespace Constants {

      static const double KILO_CONV_FACTOR= 1.0e+03;
      static const double MEGA_CONV_FACTOR= 1.0e+06;
      static const double GIGA_CONV_FACTOR= 1.0e+09;

      static const double GRAMS_2_KILOGRAMS= 1.0/KILO_CONV_FACTOR;
    
      static const double KPASCAL_2_PASCAL= KILO_CONV_FACTOR;
      static const double MPASCAL_2_PASCAL= KPASCAL_2_PASCAL*KPASCAL_2_PASCAL;

      static const double PASCAL_2_KPASCAL= 1.0/KILO_CONV_FACTOR;
      static const double PASCAL_2_MPASCAL= 1.0/MEGA_CONV_FACTOR;
    
      static const double BAR_2_PASCAL=  1.0e+05;    
      static const double KBAR_2_PASCAL= KILO_CONV_FACTOR*BAR_2_PASCAL;
    
      static const double KBAR_2_KPASCAL= BAR_2_PASCAL;    
      static const double KBAR_2_MPASCAL= BAR_2_PASCAL/KILO_CONV_FACTOR;
      static const double KBAR_2_GPASCAL= BAR_2_PASCAL/MEGA_CONV_FACTOR;

      static const double KPASCAL_2_KBAR= 1.0/KBAR_2_KPASCAL;    
      static const double MPASCAL_2_KBAR= 1.0/KBAR_2_MPASCAL;
      static const double GPASCAL_2_KBAR= 1.0/KBAR_2_GPASCAL;      
      
      static const double CELSIUS_2_KELVINS= 273.15;
      static const double KELVINS_2_CELSIUS= -273.15;

      //--- Constant ScalarQuantity objects:
  
      //static const ScalarQuantity STD_PRESSURE= ScalarQuantity(100.0e3, 0.0, Pa); //--- IUPAC (STP) since 1982. TODO provide reference
      static const ScalarQuantity STD_PRESSURE= ScalarQuantity(1.0, 0.0, bar);
      static const ScalarQuantity STD_TEMPERATURE= ScalarQuantity(298.15, 0.0, K); //--- IUPAC (STP) since 1982. TODO provide reference
    
      //--- Avogadro's number is now exact(since May 20 2019. TODO: provide reference ! ).
      static const ScalarQuantity AVOGADRO_NUMBER= ScalarQuantity(6.02214076e23, 0.0, _mole);

      static const ScalarQuantity IDEAL_GAS_CONSTANT= ScalarQuantity(8.3144598, 4.8e-06, J_moleK);

    };
  };
};
    
#endif
