//-*-c++-*-
#ifndef _NPGTOSExtensive_hpp
#define _NPGTOSExtensive_hpp

//---
#include "NPGTOS.hpp"

//---
namespace NPGTOS {

  namespace Extensive {

    typedef enum { MASS,
		   VOLUME,
                   NB_MOLES,
                   ENTROPY,
                   GIBBS_FE,
                   ENTHALPY,
                   INTERNAL_E,
                   HELMHOLTZ_FE } QIndexT;

    static const int NB_EXT_QUANTITIES= HELMHOLTZ_FE+1;
    
    class Quantities;

  };
};

#endif
