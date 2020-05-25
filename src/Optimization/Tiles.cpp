//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "System/System.hpp"
#include "Optimization/Tiles.hpp"

//---
using namespace NPGTOS;

//---
Optimization::Tiles::Tiles() {
  this->init();
}

//---
Optimization::Tiles::~Tiles() {
  this->init();
}

//---
Optimization::Tiles& Optimization::Tiles::init() {

  if (this->nodesTiles) delete [] this->nodesTiles;

  this->nodesTiles= NULL;

  this->nbNodeTiles= 0;
}

