#ifndef __TREASURE_MERCHANT_H__
#define __TREASURE_MERCHANT_H__

#include "treasure.h"

class Treasure_Merchant : public Treasure {
  static int const TREASURE_MERCHANT_VALUE = 4;
public:
  static int const SPAWN_RATE = 0;
  Treasure_Merchant();
};

#endif
