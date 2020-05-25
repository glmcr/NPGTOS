//-*-c++-*-

//---
#include "NPGTOS.hpp"
//#include "Core/Core.hpp"
#include "System/System.hpp"
#include "System/Node.hpp"

//---
using namespace NPGTOS;

//---
System::Node::Node() :
  Extensive::Quantities::Quantities(),
  Intensive::EnvScalarQuantities::EnvScalarQuantities() {
  
  //this->init();
}

//---
System::Node::~Node() { }

// //---
// Optimization::Node::~Node() {
//   //this->DynamicLineup::~DynamicLineup();
//   this->init();
// }


