//-*-c++-*-

//----
#include <cstdbool>
#include <string>
#include <array>
#include <vector>
#include <iostream>

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Constants.hpp"
#include "System/System.hpp"
#include "Core/ScalarQuantity.hpp"

//---
#include "Tensors/Tensors.hpp"
#include "Tensors/Ord2Tensor.hpp"

//---
using namespace NPGTOS;
using namespace NPGTOS::Core;
using namespace NPGTOS::System;

//---
int main(int argc, char* argv[]) {
  
  std::cout << "ChemStateT::EQUILIBRIUM="        << ChemStateT::EQUILIBRIUM << std::endl;
  std::cout << "IDEAL_GAS_CONSTANT.value="       << Constants::IDEAL_GAS_CONSTANT.getValue() << std::endl; 
  std::cout << "IDEAL_GAS_CONSTANT.uncertainty=" << Constants::IDEAL_GAS_CONSTANT.getUncertainty() << std::endl;
  std::cout << "IDEAL_GAS_CONSTANT.unit="        << Constants::IDEAL_GAS_CONSTANT.getUnit() << std::endl;
  std::cout << "AVOGADRO_NUMBER.value="          << Constants::AVOGADRO_NUMBER.getValue() << std::endl;

  ScalarQuantity vq= ScalarQuantity(69.0,0.0,Core::UNDEFINED); //.set(69.0,0.0,Core::UNDEFINED);
  
  std::cout << "vq value 1=" << vq.getValue() << std::endl;

  //--- Deep copy here:
  Core::ScalarQuantity vqt= vq;

  vqt.setValue(0.42);

  std::cout << "vqt value=" << vqt.getValue() << std::endl; 

  std::cout << "vq value aft=" << vq.getValue() << std::endl; 

  Tensors::Ord2Tensor sm; //= { .data[0]= 1.0, .data[1]= 2.0, .data[2]= 
  sm.r0.i= 1.0; sm.r0.j= 2.0; sm.r0.k= 3.0;
  sm.r1.i= 2.0; sm.r1.j= 4.0; sm.r1.k= 5.0;
  sm.r2.i= 3.0; sm.r2.j= 5.0; sm.r2.k= 6.0;

  Tensors::Ord2Tensor::show(&sm,"sm");

  Tensors::Ord2Tensor mr;
  mr.r0.i= 1.0; mr.r0.j= 2.0; mr.r0.k= 3.0;
  mr.r1.i= 4.0; mr.r1.j= 5.0; mr.r1.k= 6.0;
  mr.r2.i= 7.0; mr.r2.j= 8.0; mr.r2.k= 9.0;

  Tensors::Ord2Tensor tmr;

  Tensors::Ord2Tensor::cpy(&mr,&tmr);

  Tensors::Ord2Tensor::show(&mr,"mr");

  Tensors::Ord2Tensor::transpose(&tmr);
  
  Tensors::Ord2Tensor::show(&tmr,"tmr");

  Tensors::Ord2Tensor ats;

  Tensors::Ord2Tensor::sub(&mr,&tmr,&ats);

  Tensors::Ord2Tensor::show(&ats,"ats");
  
  std::cout << "sm:ats=" << Tensors_O2O2_DDPR(&sm,&ats) << std::endl;
  //std::cout << "sm:ats=" << Tensors_O2O2_DDP(sm,ats) << std::endl;
  
  //vq.setValue(-69.69);
  //std::cout << "vq value 2=" << vq.getValue() << std::endl;

  // Component cp= Component();
  // cp.setChemPotentialValue(-69.69);
  // std::cout << "cp chempot value=" << cp.getChemPotentialValue() << std::endl;
  // OpenSystemComponent oscp= OpenSystemComponent();
  // oscp.setSystemMassValue(42.42);
  // std::cout << "oscp SystemMass=" << oscp.getSystemMassValue() << std::endl;

  //std::string blah= "blah";
  //std::string* bp;
  //bp= &blah;
  
  return 0;
}
  
