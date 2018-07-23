#ifndef _DWARF_H_
#define _DWARF_H_

#include "enemy.h"
#include <memory>

class Player;

class Dwarf: public Enemy {
 public:
   Dwarf();
   atkStatus wasAttacked(std::shared_ptr<Player>player) override;
};

#endif
