#ifndef GRID_H
#define GRID_H
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "textdisplay.h"
#include "cell.h"

class MyMapNotFoundException : public std::exception {
public:
  virtual const char *what() const noexcept;
};

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  std::vector<std::vector<Cell *>> chambers; // Cell& sorted into chambers
  std::unique_ptr<TextDisplay> td;  // The text display.
  int level;  // What level does this grid represent
    // Add private members, if necessary.
  void assignChamber(Cell &cell, int n);
  void findChambers();
public:
  Grid();

  void init(const std::string &fname, int n); // Sets up a new grid by reading
                                              // from fname in mapFolder

  Cell getCell(int row, int col) const;
  int getWidth() const;
  int getHeight() const;

  void printChambers();

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
