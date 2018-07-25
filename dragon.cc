#include "dragon.h"
#include "treasure_dragon.h"


Dragon::Dragon(Treasure_Dragon * hoard): 
  Enemy('D', "Dragon", 150, 20, 20), Hoard{hoard} {}

Treasure_Dragon * Dragon::getHoard() const {
  return Hoard;
}
