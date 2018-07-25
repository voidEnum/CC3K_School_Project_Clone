#ifndef _ORC_H_
#define _ORC_H_
#include "enemy.h"
#include <memory>

class Player;

class Orc: public Enemy {
 public:
   Orc();
   atkStatus attack(std::shared_ptr<Player> p) override;
   std::string actionText(std::shared_ptr<Player>p, atkStatus as) override;
};

#endif
