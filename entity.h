#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <memory>
#include <string>
#include "posn.h"

class Creature;
class Player;

enum class atkStatus {EmptyTarget, InvalidTarget, Miss, Hit, Kill};

class Entity {
protected:
  Posn pos;
  char symbol;
  std::string name;
public:
  Entity(char sym = 'Y', std::string name = "Entity");
  virtual atkStatus wasAttacked(Creature *aggressor);
  //virtual atkStatus wasAttacked(Player *aggressor);
  template<typename T> 
  atkStatus wasAttacked(T aggressor) {
    (void)aggressor;
    return atkStatus::InvalidTarget;
  }
  virtual char getSymbol() const;
  virtual std::string getName() const;
  void setPos(Posn p);
  Posn getPosn() const;
};

#endif
