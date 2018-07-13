#include "grid.h"

#include <vector>
#include "observer.h"
#include "subject.h"
#include "textdisplay.h"

using namespace std;

Grid::~Grid() {
  delete td;
  delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob) {
  this->ob = ob;
}

bool Grid::isFull() const {
  // If any cell is found without a colour, the grid is not full so
  // return false
  for (auto it = theGrid.begin(); it != theGrid.end(); it++) {
    for (auto itt = it->begin(); itt != it->end(); itt++) {
      if (itt->getInfo().colour == Colour::NoColour) {
        return false;
      }
    }
  }
  return true;
}

Colour Grid::whoWon() const {
  int blackCount = 0;
  int whiteCount = 0;

  for (auto it = theGrid.begin(); it != theGrid.end(); it++) {
    for (auto itt = it->begin(); itt != it->end(); itt++) {
      if (itt->getInfo().colour == Colour::Black) {
        blackCount++;
      }else if (itt->getInfo().colour == Colour::White) {
        whiteCount++;
      }
    }
  }

  if (blackCount > whiteCount) {
    return Colour::Black;
  } else if (whiteCount > blackCount) {
    return Colour::White;
  } else {
    return Colour::NoColour;
  }
}

void Grid::init(size_t n) {
  if ((n % 2) != 0 || n < 4) {
    throw InvalidMove();
  }
  theGrid.clear();
  theGrid.reserve(n);

  // destroy existing TextDisplay if it exists
  delete td;
  // set td to point at a new TextDisplay
  td = new TextDisplay(n);

  for (int row = 0; row < (int) n; row ++) {
    // add new row
    theGrid.push_back(vector<Cell>());
    theGrid.back().reserve(n);
    for (int col = 0; col < (int) n; col++) {
      // add new cell
      theGrid.back().push_back(Cell(row, col));
      // attach the text display to the new cell
      theGrid[row][col].attach(td);
    }
  }

  // Loop through the entire grid again
  // For each cell, check if each neighbour is in range, if it is
  // attach the neighbour to the cell as an observer
  for (int row = 0; row < (int) n; row++) { 
    for (int col = 0; col < (int) n; col++) {
      if (row -1 >= 0) {
        theGrid[row][col].attach(&(theGrid[row-1][col]));
      }
      if (row -1 >= 0 && col+1 < (int) n) {
        theGrid[row][col].attach(&(theGrid[row-1][col+1]));
      }
      if (col +1 < (int) n) {
        theGrid[row][col].attach(&(theGrid[row][col+1]));
      }
      if (row + 1 < (int) n && col + 1 < (int) n) {
        theGrid[row][col].attach(&(theGrid[row+1][col+1]));
      }
      if (row + 1 < (int) n)  {
        theGrid[row][col].attach(&(theGrid[row+1][col]));
      }
      if (row + 1 < (int) n && col-1 >= 0)  {
        theGrid[row][col].attach(&(theGrid[row+1][col-1]));
      }
      if (col -1 >= 0)  {
        theGrid[row][col].attach(&(theGrid[row][col-1]));
      }
      if (col-1 >= 0 && row -1 >= 0)  {
        theGrid[row][col].attach (&(theGrid [row-1][col-1]));
      }
    }
  }
  // Set starting pieces to the right colour
  theGrid[n/2 - 1][n/2 - 1].setPiece(Colour::Black);
  theGrid[n/2 - 1][n/2].setPiece(Colour::White);
  theGrid[n/2][n/2 - 1].setPiece(Colour::White);
  theGrid[n/2][n/2].setPiece(Colour::Black);
}

void Grid::setPiece(size_t r, size_t c, Colour colour) {
  if (theGrid.size() == 0 || r >= theGrid.size() || c >= theGrid.size() ||
      theGrid[r][c].getInfo().colour != Colour::NoColour) {
    throw InvalidMove();
  }else {
    theGrid[r][c].setPiece(colour);
  }
}

void Grid::toggle(size_t r, size_t c) {
  theGrid[r][c].toggle();
}

ostream &operator<<(ostream &out, const Grid &g) {
  return out << *(g.td);
}
