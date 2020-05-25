//-*-c++-*-
#ifndef _NPGTOSCoreNomenclature_hpp
#define _NPGTOSCoreNomenclature_hpp

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
//#include "Core/Constants.hpp"

//---
//using namespace NPGTOS;

//---
class Core::Nomenclature {

  private :
  
    std::string name;    //--- Long name(e.g. kyanite )
    std::string abbrev;  //--- Abbreviation (e.g. Ky, or None when no abbreviation)
    std::string formula; //--- Al2SiO5
  
  //const std::string *restrict name;   //--- Long name(e.g. kyanite )
  //const std::string *restrict abbrev; //--- Abbreviation (e.g. Ky, or None when no abbreviation)
  //const std::string *restrict formula; //--- Al2SiO5

    virtual inline Nomenclature& init(); // final; 

 protected:

    //--- Provide an update method for polymorphic phases changes:
    //    Note: formula stays the same for all polymorphic phases changes ??
    virtual inline const Nomenclature& updateNomenclature(const std::string& NewName,
				                          const std::string& NewAbbrev,
					                  const std::string& NewFormula) final;   
  public :

    Nomenclature();
  
    Nomenclature(const std::string& Name,
		 const std::string& Abbrev,
		 const std::string& Formula);
  
    ~Nomenclature();

    
    virtual inline const std::string& getName() const final;
    virtual inline const std::string& getAbbrev() const final;
    virtual inline const std::string& getFormula() const final;
};

//---
inline const std::string& Core::Nomenclature::getName() const {
  return this->name;
}

//---
inline const std::string& Core::Nomenclature::getAbbrev() const {
  return this->abbrev;
}

//---
inline const std::string& Core::Nomenclature::getFormula() const {
  return this->formula;
}

//---
inline Core::Nomenclature& Core::Nomenclature::init() {

  this->name.clear();
  this->abbrev.clear();
  this->formula.clear();

  return *this;
}

//---
inline const Core::Nomenclature&
   Core::Nomenclature::updateNomenclature(const std::string& NewName,
				          const std::string& NewAbbrev,
					  const std::string& NewFormula) {
  //this->name->assign(NewName);
  
  this->name= NewName;
  this->abbrev= NewAbbrev;
  this->formula= NewFormula;
  
  return *this;
}

//static inline std::ostream & operator<<(std::ostream& os,  al) {
//  return os << static_cast<char>(al);
//}

#endif

