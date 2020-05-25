//-*-c++-*-
#ifndef _NPGTOSCore_hpp
#define _NPGTOSCore_hpp

//---
#include "NPGTOS.hpp"
#include "Core/CMacros.hpp"

//---
namespace NPGTOS {

  namespace Core {

    typedef enum { UNITLESS,
		   moles,    //--- Avoiding confusion with meters.  
		   meters,   //--- Avoiding confusion with moles.
		   time,     //--- Avoiding T,t confusion.
		   Kg,       //--- Ok.
                   grams,    //---
		   m3,       //--- cubic meters
		   cm3,      //--- cubic centimeters
		   J,        //--- Joules
		   KiloJ,    //---
		   Pa,       //--- Pascals
		   bar,      //--- Ok.
		   Kbar,     //--- Ok (Only here for conversions, using Pa in computations).
		   K,        //--- Kelvins
		   _mole,    //--- exp(moles,-1)
		   _meter,   //--- exp(meters,-1)
		   J_mole,   //--- Chemical potential unit. 
		   J_K,      //--- Joules/Kelvins
		   J_Kg,     //--- Joules/Kg(for specific energies types)
		   J_KgK,    //--- Joules/(kg*Kelvins) (for specific entropy)
		   J_moleK,  //--- Joules/(mole*Kelvins) (molar entropy)
		   Kg_m3,    //--- rho (a.k.a specific gravity)
		   m3_Kg,    //--- Specifc volume
		   m3_mole,  //--- molar volume
                   grams_cm3, //--- 
		   cm3_grams, //---
		   cm3_mole, //---		   
		   kg_mole,  //--- molar mass
		   grams_mole,   //---
		   K_time,   //--- Temperature/time
		   UNDEFINED } UnitsT;

    //---
    //typedef enum { KbarToKPa, KbarToMPa, KbarToGpa } PressureUnitConversions;

    //---
    typedef enum { MOLAR,
		   MASS,
		   VOLUME
                 } FractionT;

    //--- TODO: Check of possible usage of oxydation states ??
    // typedef enum { MINUS_6= -6,
    // 		   MINUS_5,
    //                MINUS_4,
    // 		   MINUS_3,
    //                MINUS_2,
    //                MINUS_1,
    //                ZERO,
    //                PLUS_1,
    //                PLUS_2,
    //                PLUS_3,
    //                PLUS_4,
    //                PLUS_5,
    //                PLUS_6 } OxidationStateT;

    class Nomenclature;

    class Component;
    class FactorizedComponent;

    class StaticMassComponent;
    class DynamicMassComponent;

    class StoichioComponent;
    class NonStoichioComponent;

    class Quantity;
    class ScalarQuantity;

  };
};

#endif
