//-*-c++-*-
#ifndef _NPGTOSSystemNode_hpp
#define _NPGTOSSystemNode_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "System/Phase.hpp"
#include "Core/Constants.hpp"
#include "Extensive/Quantities.hpp"
#include "Intensive/EnvScalarQuantities.hpp"

//---
using namespace NPGTOS;

//--- We can compare an System::Node object to
//    a kind of a dynamic assemblage(system) of phases
//    (with the extreme possibility of the presence of
//     only one phase)
class System::Node :
  public Extensive::Quantities,
  public Intensive::EnvScalarQuantities { 

  private :

  protected :

    //--- std::vector of Phase objects:
    //    Intended to be used as a dynamic subset
    //    of stable(or quasi-stable) phases
    //    in a particular thermodynamic context.
    //    Phase objects can be added or removed
    //    at will.
    std::vector<Phase *> phases;

    //--- Could use the Extensive::Quantities for a Node
    //    i.e. the sums of Phase objects Extensive::Quantities
    //Extensive::Quantities extQuantities;    
  
  public :

    Node();
    ~Node();

    virtual inline unsigned int size() const final;
};

//---
inline unsigned int System::Node::size() const {

  return this->phases.size();
}

#endif
