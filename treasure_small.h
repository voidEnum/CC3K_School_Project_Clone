#ifndef __TREASURE_SMALL_H__
#define __TREASURE_SMALL_H__

#include "treasure.h"

class Treasure_Small : public Treasure {
  static int const TREASURE_SMALL_VALUE = 1;
public:
  static int const SPAWN_RATE = 2;
  Treasure_Small();
};

#endif
