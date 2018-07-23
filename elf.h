#ifndef _ELF_H_
#define _ELF_H_
#include "enemy.h"
#include <memory>

class Player;

class Elf: public Enemy {
 public:
   Elf();
   std::string actionText(std::shared_ptr<Player>p, atkStatus as) override;
};
#endif
