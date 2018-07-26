#ifndef _DROW_H_
#define _DROW_H_

#include <memory>
#include "player.h"

class Drow: public Player {
 public:
  Drow();  
  void useEntity(Potion_RH &p) override; 
  void useEntity(Potion_PH &p) override; 
  void useEntity(Potion_BA &p) override; 
  void useEntity(Potion_BD &p) override; 
  void useEntity(Potion_WA &p) override; 
  void useEntity(Potion_WD &p) override; 
};

#endif

