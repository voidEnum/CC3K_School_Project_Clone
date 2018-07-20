#include <iostream>
#include <string>
#include <memory>

#include "grid.h"
#include "creature.h"
#include "player.h"
#include "game.h"
#include "controller.h"
using namespace std;

int main() {
  Game theGame();
  Controller theController(cin);

  theController.getCommand();
  theController.sendRace();

  while (true) {
    theController.getCommand();
    theController.sendCommand();
  }
}


/*
int main() {

  Grid grid;

  try {
    grid.init("maps/basicFloor.txt", 1);
  } catch (MyMapNotFoundException e) {
    cout << e.what() << endl;
    return -1;
  }
  cout << grid;
  
  string s;
  cout << "Enter Command: (help for cmd list)" << endl;
  while (cin >> s) { 
    if (s == "help") {
      cout << "me sourceR sourceC targertR targetC" << endl;
      cout << "pe targetR targetC" << endl;
      cout << "re targetR targetC" << endl;
      cout << "q to quit" << endl;
    } else if (s == "pe") {
      int r, c;
      cin >> r;
      cin >> c;
      shared_ptr<Entity> toPlace(new Creature());
      grid.placeEntity(toPlace, grid.getCell(r, c));
      cout << grid;
    } else if (s == "re") {
      int r, c;
      cin >> r;
      cin >> c;
      grid.removeEntity(grid.getCell(r, c));
      cout << grid;
    } else if (s == "me") {
      int sr, sc, tr, tc;
      cin >> sr;
      cin >> sc;
      cin >> tr;
      cin >> tc;
      grid.moveEntity(grid.getCell(sr, sc), grid.getCell(tr,tc));
      cout << grid;
    } else if (s == "q") {
      break;
    }
    cout << "Enter Command: (help for cmd list)" << endl;
  }
  while (1) {  
    processturn();
  }
    
  
}
*/
