#include "grid.h"

#include <fstream>
#include "cell.h"
#include "textdisplay.h"

using namespace std;

const char * MyMapNotFoundException::what() const noexcept {
    return "Tried to load a non existent map";
}

Grid::Grid(): theGrid(), td{new TextDisplay()}, level{0} {}

Grid::~Grid() {
  delete td;
}

void Grid::init(const string &fname, const int n) {

  vector<vector<Cell>> newGrid; // Temporary vector used to build the new grid

  string s;
  ifstream inFile(fname);

  if (!inFile.is_open()) {
    throw MyMapNotFoundException();
  }

  int row = 0, col = 0;
  while (getline(inFile, s)) {
    newGrid.push_back(vector<Cell>());
    vector<Cell> &v = newGrid.back();
    for (auto it = s.begin(); it != s.end(); it++) {
      switch (*it) {
        case '|' : v.push_back(Cell(row, col, Terrain::VertWall));  break;
        case '-' : v.push_back(Cell(row, col, Terrain::HoriWall));  break;
        case '.' : v.push_back(Cell(row, col, Terrain::ChamFloor)); break;
        case '#' : v.push_back(Cell(row, col, Terrain::PassFloor)); break;
        case '+' : v.push_back(Cell(row, col, Terrain::Door));      break;
        default  : v.push_back(Cell(row, col, Terrain::Empty));     break;
      }
      col++;
    }
    row++;
  }
  
  theGrid.swap(newGrid);
  level = n;

  td->buildDisplay(*this);
}

int Grid::getWidth() const {
  if (theGrid.size()) {
    return theGrid[0].size();
  }else {
    return 0;
  }
}

int Grid::getHeight() const {
  return theGrid.size();
}

Cell Grid::getCell(int row, int col) const {
  return theGrid[row][col];
}

ostream &operator<<(ostream &out, const Grid &g) {
  return out << *(g.td);
}
