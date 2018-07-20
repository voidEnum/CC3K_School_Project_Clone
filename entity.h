#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "posn.h"

class Creature;
class Player;

enum class atkStatus {EmptyTarget, InvalidTarget, Miss, Hit, Kill};

class Entity {
protected:
  Posn pos;
  char symbol;
public:
  Entity(Posn p, char sym);
  virtual atkStatus wasAttacked(Creature *aggressor);
  //virtual atkStatus wasAttacked(Player *aggressor);
  template<typename T> 
  atkStatus wasAttacked(T aggressor) {
    (void)aggressor;
    return atkStatus::InvalidTarget;
  }
  virtual char getSymbol() const;
  virtual void setPos(Posn p);
};

#endif
