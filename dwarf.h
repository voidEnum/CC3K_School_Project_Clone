#ifndef _DWARF_H_
#define _DWARF_H_

#include "enemy.h"

class Dwarf: public Enemy {
 public:
   Dwarf(shared_ptr<Cell> cellptr);
};

#endif
