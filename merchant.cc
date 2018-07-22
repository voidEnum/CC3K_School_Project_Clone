#include "merchant.h"


Merchant::Merchant(): 
   Enemy{'M', "Merchant", 30, 70, 5}, isHostile{false} {}


void Merchant::turnHostile() {
  isHostile = true;
}

bool Merchant::checkHostile() {
  return isHostile;
}
