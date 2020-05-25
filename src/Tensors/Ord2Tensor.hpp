//-*-c++-*-
#ifndef _Ord2Tensor_hpp
#define _Ord2Tensor_hpp

//--- <cstring> for memset and memcpy handy C utilities
//#include <cstring>

//---
#include "Tensors/Ord1Tensor.hpp"

//---
using namespace NPGTOS;

//---
struct Tensors::Ord2Tensor {

  Ord1Tensor r0;
  Ord1Tensor r1;
  Ord1Tensor r2;
  
  //double data[ORD2_DIM];

  static inline Ord2Tensor* init(double initValue, Ord2Tensor* const O2);
  
  static inline void show(const Ord2Tensor* const O2, const std::string& name);
  
  static inline Ord2Tensor* transpose(Ord2Tensor* const O2);
  
  static inline Ord2Tensor* add(const Ord2Tensor* const restrict O21,
				const Ord2Tensor* const restrict O22, Ord2Tensor* const restrict O2R);

  static inline Ord2Tensor* cpy(const Ord2Tensor* const restrict O2F, Ord2Tensor* const restrict O2T);  
  
  static inline Ord2Tensor* sub(const Ord2Tensor* const restrict O21,
				const Ord2Tensor* const restrict O22, Ord2Tensor* const restrict O2R);
};

//---
inline Tensors::Ord2Tensor* Tensors::Ord2Tensor::init(double initValue, Ord2Tensor* const O2) {

  Tensors::Ord1Tensor::init(initValue, &O2->r0);
  Tensors::Ord1Tensor::init(initValue, &O2->r1);
  Tensors::Ord1Tensor::init(initValue, &O2->r2);
  
  // OO
  //O2.r0.init(initValue);
  //O2.r1.init(initValue);
  //O2.r2.init(initValue);
  
  return O2;
}
  
//---
inline Tensors::Ord2Tensor* Tensors::Ord2Tensor::add(const Tensors::Ord2Tensor* const restrict O21,
				                     const Tensors::Ord2Tensor* const restrict O22,
						           Tensors::Ord2Tensor* const restrict O2R) {

  //--- TODO1: Put some _WTF checks:
  //    TODO2: 3 Threads for that ??

  Ord1Tensor::add(&O21->r0, &O22->r0, &O2R->r0);
  Ord1Tensor::add(&O21->r1, &O22->r1, &O2R->r1);
  Ord1Tensor::add(&O21->r2, &O22->r2, &O2R->r2);
  
  // O2R->data[0]= O21->data[0] + O22->data[0];
  // O2R->data[1]= O21->data[1] + O22->data[1];
  // O2R->data[2]= O21->data[2] + O22->data[2];

  // O2R->data[3]= O21->data[3] + O22->data[3];
  // O2R->data[4]= O21->data[4] + O22->data[4];
  // O2R->data[5]= O21->data[5] + O22->data[5];

  // O2R->data[6]= O21->data[6] + O22->data[6];
  // O2R->data[7]= O21->data[7] + O22->data[7];
  // O2R->data[8]= O21->data[8] + O22->data[8];
  
  return O2R;
}

//---
inline Tensors::Ord2Tensor* Tensors::Ord2Tensor::cpy(const Tensors::Ord2Tensor* const restrict O2F, Tensors::Ord2Tensor* const restrict O2T) {

  Tensors::Ord1Tensor::cpy(&O2F->r0, &O2T->r0);
  Tensors::Ord1Tensor::cpy(&O2F->r1, &O2T->r1);
  Tensors::Ord1Tensor::cpy(&O2F->r2, &O2T->r2);
  
  //memcpy(&O2T->r0, &O2F->r0, Tensors::ORD1_DIM*sizeof(double));
  //memcpy(&O2T->r1, &O2F->r1, Tensors::ORD1_DIM*sizeof(double));
  //memcpy(&O2T->r2, &O2F->r2, Tensors::ORD1_DIM*sizeof(double));
  
  //memcpy(&O2T->data[0], &O2F->data[0], Tensors::ORD2_DIM*sizeof(double));  
  //memcpy(&O2T, &O2F, sizeof(
  
  return O2T;
}

//---
inline Tensors::Ord2Tensor* Tensors::Ord2Tensor::sub(const Tensors::Ord2Tensor* const restrict O21,
				                     const Tensors::Ord2Tensor* const restrict O22,
						           Tensors::Ord2Tensor* const restrict O2R) {

  //--- TODO1: Put some _WTF checks:
  //    TODO2: 3 Threads for that ??

  Ord1Tensor::sub(&O21->r0, &O22->r0, &O2R->r0);
  Ord1Tensor::sub(&O21->r1, &O22->r1, &O2R->r1);
  Ord1Tensor::sub(&O21->r2, &O22->r2, &O2R->r2);
  
  // O2R->data[0]= O21->data[0] - O22->data[0];
  // O2R->data[1]= O21->data[1] - O22->data[1];
  // O2R->data[2]= O21->data[2] - O22->data[2];

  // O2R->data[3]= O21->data[3] - O22->data[3];
  // O2R->data[4]= O21->data[4] - O22->data[4];
  // O2R->data[5]= O21->data[5] - O22->data[5];

  // O2R->data[6]= O21->data[6] - O22->data[6];
  // O2R->data[7]= O21->data[7] - O22->data[7];
  // O2R->data[8]= O21->data[8] - O22->data[8];
  
  return O2R;
}

//---
inline Tensors::Ord2Tensor* Tensors::Ord2Tensor::transpose(Tensors::Ord2Tensor* const O2) {

  //--- O2: [ 0:->(0,0) 1:->(0,1) 2:->(0,2)
  //          3:->(1,0) 4:->(1,1) 5:->(1,2)
  //          6:->(2,0) 7:->(2,1) 8:->(2,2) ]

  const double sup0j= O2->r0.j;
  const double sup0k= O2->r0.k;
  const double sup1k= O2->r1.k;

  O2->r0.j= O2->r1.i;
  O2->r0.k= O2->r2.i;
  O2->r1.k= O2->r2.j;

  O2->r1.i= sup0j;
  O2->r2.i= sup0k;
  O2->r2.j= sup1k;
  
  // const double sup01= O2->data[1];
  // const double sup02= O2->data[2];
  // const double sup12= O2->data[5];

  // O2->data[1]= O2->data[3];
  // O2->data[2]= O2->data[6];
  // O2->data[5]= O2->data[7];
  
  // O2->data[3]= sup01;
  // O2->data[6]= sup02;
  // O2->data[7]= sup12;

  return O2;
}

//--- 
inline void Tensors::Ord2Tensor::show(const Ord2Tensor* const O2, const std::string& name) {

  std::cout << name << "::row0= | " << O2->r0.i << " " << O2->r0.j << " " << O2->r0.k << " |" << std::endl;
  std::cout << name << "::row1= | " << O2->r1.i << " " << O2->r1.j << " " << O2->r1.k << " |" << std::endl;
  std::cout << name << "::row2= | " << O2->r2.i << " " << O2->r2.j << " " << O2->r2.k << " |" << std::endl;
  
  // std::cout << name << "::row0= | " << O2->data[0] << " " << O2->data[1] << " " << O2->data[2] << " |" << std::endl;
  // std::cout << name << "::row1= | " << O2->data[3] << " " << O2->data[4] << " " << O2->data[5] << " |" << std::endl;
  // std::cout << name << "::row2= | " << O2->data[6] << " " << O2->data[7] << " " << O2->data[8] << " |" << std::endl;
}

#endif
