//-*-c++-*-
#ifndef _NPGTOSOptimizationStaticMassNodesTile_hpp
#define _NPGTOSOptimizationStaticMassNodesTile_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Constants.hpp"
#include "System/System.hpp"
#include "Optimization.hpp"
#include "Optimization/NodesTile.hpp"
#include "Core/StaticMassComponent.hpp"
//#include "Optimization/StaticMassNode.hpp"

//---
using namespace NPGTOS;

//--- 
class Optimization::StaticMassNodesTile final :public Optimization::NodesTile {

  private :
  
  protected :

    //--- Array of Core::StaticMassComponent objects supposed to be allocated
    //    at the beginning of the computations only..
    Core::StaticMassComponent* restrict SMComponents;

    virtual inline StaticMassNodesTile& init() final override;
    
  public :
  
    StaticMassNodesTile();
    //StaticMassNodesTile(unsigned int nbDimensions, unsigned int totalNbOfNodes);
    ~StaticMassNodesTile();
};

//---
inline Optimization::StaticMassNodesTile& Optimization::StaticMassNodesTile::init() {

  if (this->SMComponents) delete [] this->SMComponents;
      
  // if (this->SMComponents) {
  //   for (int smc=0; smc< this->nbComponents; smc++) {
  //      delete this->SMComponents[smc];
  //   }
  //   delete [] this->SMComponents;
  // }

  this->SMComponents= NULL;
  
  //if (this->smNodes) delete [] this->smNodes;
  //this->smNodes= NULL;
  //return *this;
}

#endif
  
