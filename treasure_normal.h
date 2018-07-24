#ifndef __TREASURE_NORMAL_H__
#define __TREASURE_NORMAL_H__

#include "treasure.h"

class Treasure_Normal : public Treasure {
  static const int TREASURE_NORMAL_VALUE = 2;
public:
  static const int SPAWN_RATE = 5;
  Treasure_Normal();
};

#endif
