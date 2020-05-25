
//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "System/System.hpp"
#include "System/StaticLineup.hpp"

//---
using namespace NPGTOS;

//---
System::StaticLineup::StaticLineup() {
  this->init();
}

//---
System::StaticLineup::~StaticLineup() {
  this->init();
}
