//-*-c++-*-

//---
#include "NPGTOS.hpp"
//#include "Core/Core.hpp"
//#include "System/System.hpp"
#include "Optimization/NodesTile.hpp"

//---
using namespace NPGTOS;

//---
Optimization::NodesTile::NodesTile() :
    System::StaticLineup::StaticLineup() {
  
  this->init();
}

//---
Optimization::NodesTile::~NodesTile() {

  this->StaticLineup::~StaticLineup();
  
  this->init();
}
