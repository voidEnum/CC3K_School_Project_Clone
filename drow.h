#ifndef _DROW_H_
#define _DROW_H_

#include <memory>
#include "player.h"

class Drow: public Player {
 public:
  Drow();  
void useEntity(Potion_RH &p); 
void useEntity(Potion_PH &p); 
void useEntity(Potion_BA &p); 
void useEntity(Potion_BD &p); 
void useEntity(Potion_WA &p); 
void useEntity(Potion_WD &p); 
};

#endif

