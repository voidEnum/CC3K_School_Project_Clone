#ifndef _ORC_H_
#define _ORC_H_
#include "enemy.h"
#include <memory>

class Player;

class Orc: public Enemy {
 public:
   Orc();
   atkStatus attack(std::shared_ptr<Player> p) override;
};

#endif