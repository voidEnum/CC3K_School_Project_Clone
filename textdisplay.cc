#include "textdisplay.h"

#include "grid.h"
#include "cell.h"

using namespace std;

void TextDisplay::buildDisplay(const Grid &g) {
  theDisplay.clear();
  int h = g.getHeight();
  int w = g.getWidth();
  for (int i = 0; i < h; i++) {
    theDisplay.push_back(vector<char>());
    vector<char> &c = theDisplay.back();
    for (int j = 0; j < w; j++) {
      switch (g.getCell(i, j).getTerrain()) {
        case Terrain::VertWall  : c.push_back('|'); break;
        case Terrain::HoriWall  : c.push_back('-'); break;
        case Terrain::ChamFloor : c.push_back('.'); break;
        case Terrain::PassFloor : c.push_back('#'); break;
        case Terrain::Door      : c.push_back('+'); break;
        default                 : c.push_back(' ');
      }
    }
  }
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
