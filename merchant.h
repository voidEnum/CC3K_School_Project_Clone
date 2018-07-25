#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include "enemy.h"
#include <memory>

class Player;

class Merchant: public Enemy {
static  bool isHostile;
 public:
   Merchant();
   void turnHostile();
   bool checkHostile();
   atkStatus attack(std::shared_ptr<Player> p) override;
}   
;
#endif
