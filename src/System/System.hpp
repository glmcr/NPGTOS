//-*-c++-*-
#ifndef _NPGTOSSystem_hpp
#define _NPGTOSSystem_hpp

//---
#include <cmath>

//---
#include "NPGTOS.hpp"
//#include "Core/Core.hpp"
#include "Core/Constants.hpp"

//---
namespace NPGTOS {

  namespace System {

    typedef enum {
                   STATIC_MASS,  //--- The mass of all components is constant(a.k.a closed thermodynamic system).
		   DYNAMIC_MASS  //--- The mass of all components could be non-constant(a.k.a open thermodynamic system).
                 } MassTypeT;

    // typedef enum {
    //                ACTIVE,
    // 		   SNOOZED
    //              } StatusT;

    typedef enum {
                   EQUILIBRIUM,      //--- a.k.a stable EQUILIBRIUM.
		   META_EQUILIBRIUM, //--- a.k.a metastable EQUILIBRIUM.
                   DISEQUILIBRIUM    //--- ok
                 } ChemStateT;

    typedef enum {
                   SOLID,
		   LIQUID,
		   GASEOUS,
		   SUPER_CRITICAL //--- a.k.a GASEOUS and LIQUID at the same time.
		                  //    (Keeping the door open for possible usage of super critical states).
                 } SLGStateT;
    
    class Phase;
    class StaticLineup;
    //class DynamicLineup;

    class Node;

    //class DynamicMassNode;
    //class VariableMassNode

  };
};

#endif
