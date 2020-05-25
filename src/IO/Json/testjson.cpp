//-*-c++-*-

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

//---
#include "jsoncpp/json/json.h"

//---
int main() {

Json::Value root;   // 'root' will contain the root value after parsing.

std::ifstream ifs ("test.json", std::ifstream::binary);

ifs >> root;
//std::cout << root;

std::string encoding =root.get("encoding", "UTF-8" ).asString();

std::cout << "encoding value=" <<encoding << std::endl;

ifs.close();

return 0;  
}


