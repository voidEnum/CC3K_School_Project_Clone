#ifndef __ENTITY_H__
#define __ENTITY_H__

class Cell;
class Creature;
class Player;

enum class atkStatus {EmptyTarget, InvalidTarget, Miss, Hit, Kill};

class Entity {
protected:
  Cell *cell;
  char symbol;
public:
  Entity(Cell *c, char sym);
  virtual atkStatus wasAttacked(Creature *aggressor);
  //virtual atkStatus wasAttacked(Player *aggressor);
  template<typename T> 
  atkStatus wasAttacked(T aggressor) {
    (void)aggressor;
    return atkStatus::InvalidTarget;
  }
  virtual char getSymbol() const;
  virtual void setCell(Cell *c);
};

#endif
