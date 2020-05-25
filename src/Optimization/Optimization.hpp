//-*-c++-*-
#ifndef _NPGTOSOptimization_hpp
#define _NPGTOSOptimization_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
//#include "Core/Constants.hpp"

//---
namespace NPGTOS {

  namespace Optimization {

    //typedef enum { } ;
    
    //typedef enum {
    //               STATIC_MASS,  //--- The mass of all components is constant(a.k.a closed thermodynamic system).
    //		     DYNAMIC_MASS  //--- The mass of all components could be non-constant(a.k.a open thermodynamic system).  
    //             } TypeT;

    class Tiles;
    
    //class Node;
    class NodesTile;

    //class StaticMassNode;
    class StaticMassNodesTile;

    //class DynamicMassNode;
    class DynamicMassNodesTile;
  };
};

#endif
