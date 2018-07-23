#ifndef _HALFLING_H_
#define _HALFLING_H_
#include "enemy.h"
#include <memory>

class Player;

class Halfling: public Enemy {
 public:
   Halfling();
   atkStatus wasAttacked(std::shared_ptr<Player>player) override;
};

#endif
