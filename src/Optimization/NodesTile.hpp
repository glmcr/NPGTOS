//-*-c++-*-
#ifndef _NPGTOSOptimizationNodesTile_hpp
#define _NPGTOSOptimizationNodesTile_hpp

//---
#include "NPGTOS.hpp"
//#include "Core/Core.hpp"
//#include "Core/Constants.hpp"
#include "System/Node.hpp"
#include "Optimization.hpp"
#include "System/StaticLineup.hpp"

//---
using namespace NPGTOS;

//--- NOTE: Only one NodesTile object per thread allowed.
//          A MPI process could then have more than one
//          NodesTile to manage.
class Optimization::NodesTile : public System::StaticLineup {

  private :
  
  protected :  

    unsigned int nbNodes;
    unsigned int nbComponents;
  
    //--- The number of Node objects is known at the
    //    beginning then we can use an array of objects
    //    instead of a std::vector to get something 
    //    which is more efficient for performance.
    System::Node* restrict nodes; 

    virtual inline NodesTile& init();
  
  public :

    NodesTile(); 
    ~NodesTile();
};

//---
inline Optimization::NodesTile& Optimization::NodesTile::init() {

  if (this->nodes) delete [] this->nodes;

  this->nodes= NULL;
  
  this->nbNodes=
    this->nbComponents= 0;

  //this->nbDimensions=0;
  
  return *this;
}

#endif
