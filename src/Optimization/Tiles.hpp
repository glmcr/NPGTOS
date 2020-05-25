//-*-c++-*-
#ifndef _NPGTOSOptimizationTiles_hpp
#define _NPGTOSOptimizationTiles_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Constants.hpp"
#include "System/System.hpp"
#include "Optimization.hpp"
#include "Optimization/NodesTile.hpp"
#include "Optimization/StaticMassNodesTile.hpp"
//#include "Optimization/DynamicMassNodesTile.hpp"

//---
using namespace NPGTOS;

//--- One Tiles object for each MPI instance and
//    one NodesTile object for each thread of a
//    MPI instance(otherwise said a given Tiles
//    object is managed by only one MPI instance)
class Optimization::Tiles final {

  private :
  
  protected :

    unsigned int nbNodeTiles;
  
    NodesTile* restrict nodesTiles; //--- The threaded NodesTile objects
                                    //    (One for each thread of a MPI instance)

    Tiles& init();
    
  public :

    Tiles();
    ~Tiles();
    
};

#endif
