//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "System/System.hpp"
#include "Optimization/StaticMassNodesTile.hpp"

//---
using namespace NPGTOS;

//---
Optimization::StaticMassNodesTile::StaticMassNodesTile() :
    Optimization::NodesTile::NodesTile() {
  
  this->init();
}

//---
Optimization::StaticMassNodesTile::~StaticMassNodesTile() {

  //--- this->init() MUST be used before this->NodesTile::~NodesTile()
  //    to avoid getting memory leaks
  this->init();
  
  this->NodesTile::~NodesTile();
}
