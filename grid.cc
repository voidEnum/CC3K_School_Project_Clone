#include "grid.h"
#include "posn.h"

#include <fstream>

#include "entity.h"
#include "treasure_dragon.h"

using namespace std;

const char * MyMapNotFoundException::what() const noexcept {
    return "Tried to load a non existent map";
}

Grid::Grid(): theGrid{vector<vector<Cell>>()}, chambers{vector<vector<Cell *>>()},
              td(new TextDisplay()),level{0} {}

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
void Grid::assignChamber(Posn p, int n) {
  Cell &cell = getCell(p);
  if (cell.getTerrain() != Terrain::ChamFloor || cell.getChamber() != 0) {
    return;
  } else {
    cell.setChamber(n);
    int r = cell.getRow(), c = cell.getCol();
    // in a properly formed map, Chamber floors will never be on the edges
    for (int i = (r - 1); i <= (r + 1); i++) {
      for (int j = (c - 1); j <= (c + 1); j++) {
        assignChamber({i, j}, n);
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
        assignChamber({col->getRow(), col->getCol()}, nextChamberNum);
        newChambers.push_back(vector<Cell *>());
        newChambers.back().push_back(&(*col));
      } else if (col->getChamber() != 0) {
        newChambers[col->getChamber() - 1].push_back(&(*col));
      }
    }
  }
  chambers.swap(newChambers);
}

vector<vector<Cell *>> & Grid::getChambers() {
  return chambers;
}

int Grid::getLevel() const {
  return level;
}

void Grid::levelUp() {
  level++;
}

void Grid::moveEntity(Posn src, Posn dest) {
  //cout << "src: " << src.r << ", " << src.c << "dest: " << dest.r << ", " << dest.c << endl;
  if (getCell(dest).getOccupant()) {
    getCell(dest).getOccupant()->beSteppedOn(*(getCell(src).getOccupant()));
  }
  getCell(dest).setOccupant(getCell(src).getOccupant());
  getCell(dest).getOccupant()->setPos(dest);
  getCell(src).setOccupant(nullptr);
  td->update(getCell(src));
  td->update(getCell(dest));
}


void Grid::placeEntity(const shared_ptr<Entity> &e, Posn placeHere) {
  e->setPos(placeHere);
  if (Treasure_Dragon *td = dynamic_cast<Treasure_Dragon *>(e.get())) {
    vector<Posn> emptyNeighbours;
    for (int i = placeHere.r - 1; i <= placeHere.r + 1; i++) {
      for (int j = placeHere.c -1; j <= placeHere.c + 1; j++) {
        if ((placeHere.r != i || placeHere.c != j) && !(getCell({i,j}).getOccupant())
             && getCell({i,j}).getTerrain() == Terrain::ChamFloor) {
          emptyNeighbours.push_back({i,j});
        }
      }
    }
    placeEntity((shared_ptr<Entity>) td->getDragon(), emptyNeighbours[rand() % 
                                                      emptyNeighbours.size()]);
  }
  getCell(placeHere).setOccupant(e);
  td->update(getCell(placeHere));
}

void Grid::removeEntity(Posn remFrom) {
  getCell(remFrom).getOccupant()->setPos({-1, -1});
  getCell(remFrom).setOccupant(nullptr);
  td->update(getCell(remFrom));
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

Cell & Grid::getCell(Posn p) {
  return theGrid[p.r][p.c];
}

void Grid::placeStairs(Posn p) {
  getCell(p).makeStairs();
  td->update(getCell(p));
}

bool Grid::hasUsable(Posn p) const {
  return theGrid[p.r][p.c].hasUsable();
}

ostream &operator<<(ostream &out, const Grid &g) {
  return out << *(g.td);
}

bool Grid::canStep(Posn p, const Entity &e) const{
  return theGrid[p.r][p.c].canStepHere(e);
}
