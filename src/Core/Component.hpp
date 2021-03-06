//-*-c++-*-
#ifndef _NPGTOSCoreComponent_hpp
#define _NPGTOSCoreComponent_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Nomenclature.hpp"
#include "Core/ScalarQuantity.hpp"

//---
//using namespace NPGTOS;

//---
class Core::Component : public Core::Nomenclature {

  private:
    
    //--- Attributes(Quantities objects) that do not vary after
    //    Component object initialization whatever we have a closed
    //    or an open system.
  
    ScalarQuantity molarMass;
    ScalarQuantity elemEntropy; //--- TODO: molar or not ?? at STP ??
  
  protected :

    bool mobility; //--- true if mobile, false otherwise(i.e. inert component)

    //--- Normal chemical potential as a scalar value
    ScalarQuantity chemPotential; 

    //--- Molar fraction could be variable for
    //    dynamic mass(a.k.a open) systems.
    ScalarQuantity molarFraction;
  
    //--- TODO: Allow the chemical potential as a tensor Quantity in components ???
    //Quantity chemPotential; 
  
    virtual inline Component& init() override;

    virtual inline Component& setMobility(bool Mobility) final;
    virtual inline Component& setChemPotentialValue(double ChemPotentialValue) final;
    virtual inline Component& setMolarFractionValue(double MolarFractionValue) final;
  
  public:

    Component();

    //--- TODO: Use a std::map<std::string> (JSON)object
    //          for a Component object initialization.
    //         
    //Component(const std::map<std::string>& ConfigMap);
    //Component(double MolarMass, double ElemEntropy, const Nomenclature& nmc);
    //~Component();

    //virtual inline Component& copy(Component& target) const;
    //virtual inline Component* const copy(Component* const target) const;  

    virtual inline bool isMobile() const final;
  //virtual inline Component& setMobility(bool Mobility) final;
  
    virtual inline double getMolarMassValue() const final;
    virtual inline double getElemEntropyValue() const final;
  
    virtual inline double getChemPotentialValue() const final;
  //virtual inline Component& setChemPotentialValue(double ChemPotentialValue) final;

    virtual inline double getMolarFractionValue() const final;
  //virtual inline Component& setMolarFractionValue(double MolarFractionValue) final;
};

//---
inline bool Core::Component::isMobile() const {

  return this->mobility;
}

//---
inline double Core::Component::getMolarMassValue() const {
  return this->molarMass.getValue();
}

//---
inline double Core::Component::getElemEntropyValue() const {
  return this->elemEntropy.getValue();
}

//---
inline double Core::Component::getChemPotentialValue() const {
  return this->chemPotential.getValue();
}

//---
inline double Core::Component::getMolarFractionValue() const {
  return this->molarFraction.getValue();
}

//---
inline Core::Component& Core::Component::init() {

  //this->factor= 0.0;

  this->molarMass= ScalarQuantity(0.0, 0.0, Core::UNDEFINED);
  this->elemEntropy= ScalarQuantity(0.0, 0.0, Core::UNDEFINED);
  
  //this->molarMass.set(0.0, 0.0, Core::UNDEFINED);
  //this->elemEntropy.set(0.0, 0.0, Core::UNDEFINED);

  this->chemPotential= ScalarQuantity(0.0, 0.0, Core::UNDEFINED);
  //this->chemPotential.set(0.0, 0.0, Core::UNDEFINED);
  //this->chemPotential= Quantity(0.0, Core::UNDEFINED);

  return *this;
}

//---
inline Core::Component& Core::Component::setChemPotentialValue(double ChemPotentialValue) {

  this->chemPotential.setValue(ChemPotentialValue);
  
  return *this;
}

//---
inline Core::Component& Core::Component::setMobility(bool Mobility) {

  this->mobility= Mobility;
  
  return *this;  
}

//---
inline Core::Component& Core::Component::setMolarFractionValue(double MolarFractionValue) {

  #ifdef _WTF
  assert(MolarFractionValue>=0.0);
  #endif
  
  this->molarFraction.setValue(MolarFractionValue);
  
  return *this;
}

#endif
