#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "item.h"
#include "posn.h"

class Treasure: public Item {
protected:
  int value;
  Treasure(int v = 2);
public:
  virtual int getValue() const final;
};

#endif
