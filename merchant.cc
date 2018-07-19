#include "merchant.h"
#include <iostream>

using namespace std;

Merchant::Merchant(shared_ptr<Cell> cellptr): 
   Enemy{cellptr, "M", 30, 70, 5} isHostile{false} {}

void Merchant::turnHostile() {
  isHostile = true;
}