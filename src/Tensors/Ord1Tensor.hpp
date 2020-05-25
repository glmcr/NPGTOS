//-*-c++-*-
#ifndef _Ord1Tensor_hpp
#define _Ord1Tensor_hpp

//--- <cstring> for memset and memcpy handy C utilities
#include <cstring>

//---
using namespace NPGTOS;

//---
struct Tensors::Ord1Tensor {

  double i;
  double j;
  double k;

  //static inline std::string& show(const Ord1Tensor* const restrict O1);
  
  static inline Ord1Tensor* init(double initValue, Ord1Tensor* const O1);

  static inline Ord1Tensor* cpy(const Ord1Tensor* const restrict O1F, Ord1Tensor* const restrict O1T);
  
  static inline Ord1Tensor* add(const Ord1Tensor* const restrict O1L,
				const Ord1Tensor* const restrict O1R,
				      Ord1Tensor* const restrict O1D);

  static inline Ord1Tensor* sub(const Ord1Tensor* const restrict O1L,
				const Ord1Tensor* const restrict O1R,
			              Ord1Tensor* const restrict O1D);  
  
  //static inline double dot(const Ord1Tensor* const restrict O1L, const Ord1Tensor* const restrict O1R);

};

// inline std::string& str(const Ord1Tensor* const restrict O1) {
//   return O1->i + " " << O1->data[1] << " " << O2->data[2]
// }

//---
inline Tensors::Ord1Tensor* Tensors::Ord1Tensor::init(double initValue, Tensors::Ord1Tensor* const O1) {

  O1->i= O1->j= O1->k= initValue;
  
  return O1;
}

inline Tensors::Ord1Tensor* Tensors::Ord1Tensor::cpy(const Tensors::Ord1Tensor* const restrict O1F,
						           Tensors::Ord1Tensor* const restrict O1T) {
  O1T->i= O1F->i;
  O1T->j= O1F->j;
  O1T->k= O1F->k;
  
  return O1T;
}

//---
inline Tensors::Ord1Tensor* Tensors::Ord1Tensor::add(const Tensors::Ord1Tensor* const restrict O1L,
		                                     const Tensors::Ord1Tensor* const restrict O1R,
		                                           Tensors::Ord1Tensor* const restrict O1D) {
  O1D->i= O1L->i + O1R->i;
  O1D->j= O1L->j + O1R->j;
  O1D->k= O1L->k + O1R->k; 
  
  return O1D;
}

//---
inline Tensors::Ord1Tensor* Tensors::Ord1Tensor::sub(const Tensors::Ord1Tensor* const restrict O1L,
		                                     const Tensors::Ord1Tensor* const restrict O1R,
		                                           Tensors::Ord1Tensor* const restrict O1D) {
  O1D->i= O1L->i - O1R->i;
  O1D->j= O1L->j - O1R->j;
  O1D->k= O1L->k - O1R->k; 
  
  return O1D;
}

//O2->data[0] << " " << O2->data[1] << " " << O2->data[2]

// //--
// inline double dot(const Tensors::Ord1Tensor* const restrict O1L, const Tensors::Ord1Tensor* const restrict O1R) {
//   return O1L->i * O1R->i + O1L->j * O1R->j + O1L->k * O1R->k;
// }

#endif
