#ifndef _ELF_H_
#define _ELF_H_

#include "enemy.h"

class Player;

class ELF: public Enemy {
 public:
   Elf(shared_ptr<Cell> cellptr);
   void attack(shared_ptr<Player> p) override;
};

#endif
