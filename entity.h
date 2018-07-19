#ifndef __ENTITY_H__
#define __ENTITY_H__

class Cell;

class Entity {
protected:
  Cell *cell;
  char symbol;
public:
  Entity(Cell *c, char sym);
  char getSymbol() const;
  void setCell(Cell *c);
};

#endif
