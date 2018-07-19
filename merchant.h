#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include "enemy.h"

class Merchant: public Enemy {
  bool isHostile = false;
 public:
   Merchant(shared_ptr<Cell> cellptr);
   void turnHostile();
};

#endif
