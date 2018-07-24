#ifndef __TREASURE_DRAGON_H__
#define __TREASURE_DRAGON_H__

#include "treasure.h"

class Treasure_Dragon: public Treasure {
  static const int TREASURE_DRAGON_VALUE = 8;
public:
  static const int SPAWN_RATE = 1;
  Treasure_Dragon();
};

#endif
