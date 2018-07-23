#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include "enemy.h"
#include <memory>

class Player;

class Merchant: public Enemy {
  bool isHostile = false;
 public:
   Merchant();
   void turnHostile();
   bool checkHostile();
   atkStatus attack(std::shared_ptr<Player> p) override;
   atkStatus wasAttacked(std::shared_ptr<Player>player) override;
};
#endif
