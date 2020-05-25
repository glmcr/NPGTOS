//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "EoS/ThermoConsts.hpp"

//---
EoS::ThermoConsts::ThermoConsts() {
  this->init();
}

//---
EoS::ThermoConsts::~ThermoConsts() {
  this->init();
}


// //---
// EoS::Constants::Constants(EoST WhichOne) {
  
//   this->init();

// //--- Connolly's Fortran
// //  
// //        else if (ieos.eq.13) then 
// // c                                 1) alpha = b1 + b2*T + b3/T + b4/T^2 
// // c                                    which is reformulated here to 
// // c                                    int(alpha,T=Tr..Tf) = b13 + b1*T + b2*T^2 + b3*ln(T) + b4/T 
// //          b2 = b2/2d0 
// //          b4 = -b4 
// //          b13 = -(b1*tr + b2*tr*tr + b3*dlog(tr) + b4/tr)
// // c                                 2)  K' is a f(T) 
// //          b9 = b9 - b10*tr*dlog(tr)

// //       else if (b8.ne.0d0) then 
// // c                                 All remaining forms (ieos = 2, 4, >100) assume:
// // c                                 1) alpha = b1 + b2*T + b3/T + b4/T^2 + b5/sqrt(T)
// // c                                    which is reformulated here to 
// // c                                    int(alpha,T=Tr..Tf) = b13 + b1*T + b2*T^2 + b3*ln(T) + b4/T + b5*sqrt(T)
// //          b2 = b2/2d0 
// //          b4 = -b4 
// //          b5 = 2d0*b5
// //          b13 = -(b1*tr + b2*tr*tr + b3*dlog(tr) + b4/tr + b5*dsqrt(tr)) 
// //

//   const bool boolBundle= ( (WhichOne == 2) || (WhichOne == 4) || (WhichOne > 100) );
  
//   if ( (WhichOne == 13) || boolBundle ) {

//     //--- b13 for EoS13
//     this->thermalExpCst= -(this->b[_1]*EOS_TSTP + 0.5*this->b[_2]*EOS_TSTP_SQE +
// 			     this->b[_3]*EOS_LN_TSTP - this->b[_4]*EOS_TSTP_INV );

//     if (boolBundle) {

//       //--- b13 for EoS2 and EoS4:
//       this->thermalExpCst -= 2.0*this->b[_5]*EOS_TSTP_SQR;

//     } 
//   }  
// }

