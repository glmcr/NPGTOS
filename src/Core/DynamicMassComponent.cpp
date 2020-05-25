//-*-c++-*-

//---
#include "NPGTOS.hpp"
#include "Core/Core.hpp"
#include "Core/DynamicMassComponent.hpp"

//---
using namespace NPGTOS;

//---
Core::DynamicMassComponent::DynamicMassComponent() :
  Core::StaticMassComponent::StaticMassComponent() { }

//---
Core::DynamicMassComponent::
  DynamicMassComponent(double SystemMass,double Uncertainty, Core::UnitsT Unit) :
    Core::StaticMassComponent::StaticMassComponent(SystemMass, Uncertainty, Unit) { }


