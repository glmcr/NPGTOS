//-*-c++-*-
#ifndef _Tensors_hpp
#define _Tensors_hpp

//---
#include "NPGTOS.hpp"

//---
#include "Tensors/TensorsMacros.hpp"

//---
namespace NPGTOS {

  //---
  namespace Tensors {
    
    static const int ORD1_DIM= 3;
    static const int ORD2_DIM= 3*ORD1_DIM;
    static const int ORD3_DIM= 3*ORD2_DIM;
    static const int ORD4_DIM= 3*ORD3_DIM;

    struct Ord1Tensor;
    struct Ord2Tensor;
    
  };
};


#endif
