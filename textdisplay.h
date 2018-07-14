#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>

class Grid;

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;
 public:

  void buildDisplay(const Grid &g);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
