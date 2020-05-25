//-*-c++-*-
#ifndef _NPGTOSEoSCrunchGaloreHub_hpp
#define _NPGTOSEosCrunchGaloreHub_hpp

//---
#include "NPGTOS.hpp"
#include "EoS/EoS.hpp"

//--- NOTE: This file(GaloreHub.hpp) is included by
//          EoS/Feed.hpp just after it includes EoS/ThermoParams.hpp
//          So no need to inlude it here(unless it is no more
//          included in EoS/Feed.hpp)
//#include "EoS/ThermoParams.hpp"

//---
namespace NPGTOS {
  
  namespace EoS {

    static double ( *const CrunchGaloreHub[CRUNCH_GALORE_DIM] )
      ( const ThermoParams& Fd, double Pressure, double Temperature )= {

      //--- NOTE: Must set undefined method pointers to NULL:
      
      ThermoParams::normalVdPPolynomial,   //--- EoS01
      ThermoParams::crunchPerpleX02X03X04, //--- EoS02
      ThermoParams::crunchPerpleX02X03X04, //--- EoS03 (Same as EoS02) 
      ThermoParams::crunchPerpleX02X03X04, //--- EoS04 (Same as EoS02)
      ThermoParams::normalVdPPolynomial,   //--- EoS07 (same as EoS01)
      ThermoParams::crunchPerpleX08,       //--- EoS08 (For H&P data solids)
      ThermoParams::crunchPerpleX09        //--- EoS09 (For H&P data liquids)
      
    }; //--- static double ( *const CrunchGaloreHub[GALORE_DIM] )
    
  }; //--- namespace EoS
  
}; //--- namespace NPGTOS

#endif
