#include "textdisplay.h"

#include "grid.h"
#include "cell.h"

#include "entity.h"

using namespace std;

void TextDisplay::buildDisplay(Grid &g) {
  theDisplay.clear();
  int h = g.getHeight();
  int w = g.getWidth();
  for (int i = 0; i < h; i++) {
    theDisplay.push_back(vector<char>());
    vector<char> &c = theDisplay.back();
    for (int j = 0; j < w; j++) {
      c.push_back(g.getCell(i, j).getSymbol());   
    }
  }
}

void TextDisplay::update(const Cell &whatChanged) {
  int r = whatChanged.getRow(), c = whatChanged.getCol();
  theDisplay[r][c] = whatChanged.getSymbol();
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (auto it = td.theDisplay.begin(); it != td.theDisplay.end(); it++) {
    for (auto itt = it->begin(); itt != it->end(); itt++) {
      out << *itt;
    }
    out << endl;
  }
  return out;
}
