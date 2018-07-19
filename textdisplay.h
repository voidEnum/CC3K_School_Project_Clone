#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>

class Grid;
class Cell;

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;
 public:

  void buildDisplay(Grid &g);
  void update(const Cell &whatChanged);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
