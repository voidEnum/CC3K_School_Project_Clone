#include <iostream>
#include "invalid_behave.h"
using namespace std;

Invalid_behave::Invalid_behave(string type): type{type} {}

string Invalid_behave::what() {
  return type;
}

