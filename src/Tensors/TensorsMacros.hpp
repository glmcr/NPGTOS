//-*-c++-*-
#ifndef _TensorsMacros_hpp
#define _TensorsMacros_hpp

//---
#include "NPGTOS.hpp"

//--- Order1(3D vectors) tensors dot product(local Ord1Tensor C structs not pointers) :
#define Tensors_O1O1_DP(O1L,O1R) ((O1L.i)*(O1R.i)+(O1L.j)*(O1R.j)+(O1L.k)*(O1R.k))

//--- Order1(3D vectors) tensors dot product(pointers to Ord1Tensor C structs) :
#define Tensors_O1O1_DPR(O1L,O1R) (((O1L)->i)*((O1R)->i)+((O1L)->j)*((O1R)->j)+((O1L)->k)*((O1R)->k))

//--- Order2(3x3 matrices) tensors double dot product(local Ord2Tensor C structs not pointers) :
//    
//    Tensors_O2O2_DDP(O2L,O2R) = O2L : O2R
//
#define Tensors_O2O2_DDP(O2L,O2R) ((Tensors_O1O1_DP(O2L.r0,O2R.r0))+(Tensors_O1O1_DP(O2L.r1,O2R.r1))+(Tensors_O1O1_DP(O2L.r2,O2R.r2)))

//--- Order2(3x3 matrices) tensors double dot product(pointers to Ord2Tensor C structs) :
#define Tensors_O2O2_DDPR(O2L,O2R) ((Tensors_O1O1_DP((O2L)->r0,(O2R)->r0))+(Tensors_O1O1_DP((O2L)->r1,(O2R)->r1))+(Tensors_O1O1_DP((O2L)->r2,(O2R)->r2)))

#endif
