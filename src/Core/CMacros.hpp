//-*-c++-*-
#ifndef _NPGTOSCoreCMacros_hpp
#define _NPGTOSCoreCMacros_hpp

#include "Core/Core.hpp"

namespace NPGTOS {
  
  namespace Core {
    
    namespace CMacros {
    
      //--- 2D and 3D array offsets stuff:
  
      //---- Column major mapping(a.k.a. Fortran indexing) : 
      #define AT2DCM(I,J,DI)           ((J)*(DI)+(I))
      #define AT3DCM(I,J,K,DI,DJ)      ((K)*(DI)*(DJ)+(J)*(DI)+(I))

      //--- Still need to validate 4D:
      //#define AT4DCM(I,J,K,L,DI,DJ,DK) ((L)*(DI)*(DJ)*(DK)+(K)*(DI)*(DJ)+(J)*(DI)+(I))

      //--- Using range struct
      //#define AT3DCMRG(II,JJ,KK,RG) ((KK)*(RG.I.Dim)*(RG.J.Dim)+(JJ)*(RG.I.Dim)+(II))
      //#define AT3DCMRGR(II,JJ,KK,RG) ((KK)*(RG->I.Dim)*(RG->J.Dim)+(JJ)*(RG->I.Dim)+(II))

      // #define AT4DCM(I,J,K,F,DI,DJ,DK) ((unsigned long)(F)*(DI)*(DJ)*(DK)+(K)*(DI)*(DJ)+(J)*(DI)+(I)) 

      //---- Row major: DECOMMISSIONED !
      //#define AT2DRM(I,J,DJ)      ((J)+(DJ)*(I))
      //#define AT3DRM(I,J,K,DJ,DK) ((K)+(DK)*((J)+(DJ)*(I)))

      //#define AT3DRMRG(I,J,K,RG) AT3DRM(I,J,K,RG.J.Dim,RG.K.Dim)
      //#define AT3DRMRG(II,JJ,KK,RG) ((KK)+(RG.K.Dim)*((JJ)+(RG.J.Dim)*(II)))
      
    };
  };
};
  
#endif
