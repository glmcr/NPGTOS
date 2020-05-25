//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/Nomenclature.hpp"

//---
//using namespace NPGTOS;
//using namespace PMCTO::Core;

//---
Core::Nomenclature::Nomenclature() {

  this->init();
}

//---
Core::Nomenclature::Nomenclature(const std::string& Name,
  		                 const std::string& Abbrev,
			         const std::string& Formula) {

  this->updateNomenclature(Name, Abbrev, Formula);
  
  //this->name= Name;
  //this->abbrev= Abbrev;
  //this->formula= Formula;
}

//---
Core::Nomenclature::~Nomenclature() {

  this->init();
}
