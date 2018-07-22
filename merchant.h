#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include "enemy.h"

class Merchant: public Enemy {
  bool isHostile = false;
 public:
   Merchant();
   void turnHostile();
   bool checkHostile();
};
#endif
