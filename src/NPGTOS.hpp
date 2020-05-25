//-*-c++-*-
#ifndef _NPGTOS_hpp
#define _NPGTOS_hpp

//----
#include <cstdbool>
#include <string>
#include <array>
#include <vector>
#include <iostream>

//--- <cassert> for debugging.
#include <cassert>

//--- Allow use of restrict keyword without the annoying leading-trailing underscores.
#define restrict __restrict__

namespace NPGTOS {

  static const int UNDEFINED= -1;
  static const std::string SNAFU_MESS = " ! -> abandon ship ! "; 

};

using namespace NPGTOS;

#endif
