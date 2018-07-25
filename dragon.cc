#include "dragon.h"
#include "treasure_dragon.h"


Dragon::Dragon(Treasure_Dragon * td): 
  Enemy('D', "Dragon", 150, 20, 20), hoard{td} {}

Treasure_Dragon * Dragon::getHoard() const {
  return hoard;
}
