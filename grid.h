#ifndef GRID_H
#define GRID_H
#include <exception>
#include <iostream>
#include <vector>
#include <string>


class TextDisplay;
class Cell;

class MyMapNotFoundException : public std::exception {
public:
  virtual const char *what() const noexcept;
};

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  TextDisplay *td = nullptr; // The text display.
  int level;  // What level does this grid represent
    // Add private members, if necessary.

public:
  Grid();
  ~Grid();

  void init(const std::string &fname, int n); // Sets up a new grid by reading
                                              // from fname in mapFolder

  Cell getCell(int row, int col) const;
  int getWidth() const;
  int getHeight() const;

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
