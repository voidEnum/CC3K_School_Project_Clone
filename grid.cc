#include "grid.h"

#include <fstream>

#include "entity.h"

using namespace std;

const char * MyMapNotFoundException::what() const noexcept {
    return "Tried to load a non existent map";
}

Grid::Grid(): theGrid(), chambers(), td(new TextDisplay()),level{0} {}

void Grid::init(const string &fname, const int n) {

  vector<vector<Cell>> newGrid; // Temporary vector used to build the new grid

  string s;
  ifstream inFile(fname);

  if (!inFile.is_open()) {
    throw MyMapNotFoundException();
  }

  int row = 0;
  while (getline(inFile, s)) {
    int col = 0;
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
  findChambers();

  td->buildDisplay(*this);
}

//  Helper function for find_Chambers. Recursively sets cell and all 
//  chamberFloor  neighbours of cell to be in chamber n.
void Grid::assignChamber(Cell &cell, int n) {
  if (cell.getTerrain() != Terrain::ChamFloor || cell.getChamber() != 0) {
    return;
  } else {
    cell.setChamber(n);
    int r = cell.getRow(), c = cell.getCol();
    // in a properly formed map, Chamber floors will never be on the edges
    for (int i = (r - 1); i <= (r + 1); i++) {
      for (int j = (c - 1); j <= (c + 1); j++) {
        assignChamber(theGrid[i][j], n);
      }
    }
  }
}

//  Helper function for init. Used after Grid is setup to sort cells into 
//  chambers
void Grid::findChambers() {
  vector<vector<Cell *>> newChambers; // Tmp vector for new chambers
  for (auto row = theGrid.begin(); row != theGrid.end(); row++) {
    for (auto col = row->begin(); col != row->end(); col++) {
      if (col->getTerrain() == Terrain::ChamFloor &&
          col->getChamber() == 0) { // current cell is chamFloor and not sorted
        int nextChamberNum = newChambers.size() + 1;
        assignChamber(*col, nextChamberNum);
        newChambers.push_back(vector<Cell *>());
        newChambers.back().push_back(&(*col));
      } else if (col->getChamber() != 0) {
        newChambers[col->getChamber() - 1].push_back(&(*col));
      }
    }
  }
  chambers.swap(newChambers);
}

void Grid::moveEntity(Cell &src, Cell &dest) {
  dest.setOccupant(src.getOccupant());
  dest.getOccupant()->setCell(&dest);
  src.setOccupant(nullptr);
  td->update(src);
  td->update(dest);
}

void Grid::placeEntity(shared_ptr<Entity> e, Cell &placeHere) {
  e->setCell(&placeHere);
  placeHere.setOccupant(e);
  td->update(placeHere);
}

void Grid::removeEntity(Cell & remFrom) {
  remFrom.getOccupant()->setCell(nullptr);
  remFrom.setOccupant(nullptr);
  td->update(remFrom);
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

Cell & Grid::getCell(int row, int col) {
  return theGrid[row][col];
}

ostream &operator<<(ostream &out, const Grid &g) {
  return out << *(g.td);
}
