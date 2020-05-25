#ifndef _NPGTOSIntensiveEnvScalarQuantities_hpp
#define _NPGTOSIntensiveEnvScalarQuantities_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Constants.hpp"
#include "Core/ScalarQuantity.hpp"
#include "Intensive/Intensive.hpp"

//---
using namespace NPGTOS;

//---
class Intensive::EnvScalarQuantities {

  private :
  
  protected :

    //--- We can consider here that pressure and temperature
    //    are averages values in a thermodynamic entity.
  
    Core::ScalarQuantity pressure;  //--- a.k.a. thermodynamic pressure here equal everywhere
                                    //    in a thermodynamic entity i.e. grad(pressure)== 0,0,0 vector. 

    Core::ScalarQuantity temperature; //--- Equal everywhere in a thermodynamic entity
                                      //    i.e. grad(temperature)== (0,0,0) vector.

    virtual inline EnvScalarQuantities& init(); // final;
  
  public :

    EnvScalarQuantities();
    //~ScalarQuantities();

    virtual inline Core::ScalarQuantity* const pressureQ() const final;    
    virtual inline Core::ScalarQuantity* const temperatureQ() const final;
};

//---
Intensive::EnvScalarQuantities& Intensive::EnvScalarQuantities::init() {

  Core::Constants::STD_PRESSURE.copyToSQDest(this->pressure);
  Core::Constants::STD_TEMPERATURE.copyToSQDest(this->temperature);
  
  return *this;
}

//---
inline Core::ScalarQuantity*
  const Intensive::EnvScalarQuantities::
    pressureQ() const { return (Core::ScalarQuantity*) &this->pressure; }

//---
inline Core::ScalarQuantity*
  const Intensive::EnvScalarQuantities::
    temperatureQ() const { return (Core::ScalarQuantity*) &this->temperature; }

#endif
