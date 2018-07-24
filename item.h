#ifndef __ITEM_H__
#define __ITEM_H__

#include "entity.h"

class Item: public Entity {
protected:
  Item(char sym = 'I', std::string name = "Item");
public:
};

#endif
