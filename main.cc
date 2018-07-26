#include <iostream>
#include <string>
#include <memory>
#include <time.h>
#include <stdlib.h>

#include "grid.h"
#include "creature.h"
#include "player.h"
#include "game.h"
#include "controller.h"
#include "invalid_behave.h"
#include "enemy.h"
using namespace std;

int main() {
  Game theGame;
  Controller theController(cin);

  srand(time(NULL));
  cout << "please select your race: (s)hade, (t)roll, (d)row, (v)ampire, (g)oblin" <<endl;
  
  //theController.getCommand();
  while (true) {
    theController.getCommand();
    try {
      theController.sendRace(theGame);
    }
    catch (Invalid_behave& ib) {
      cout << ib.what() << endl;
      continue;
    }
    break;
  }
  theController.requestDisplay(theGame, "The player entered the dungeon");

  while (!theGame.gameOver()) {
    try {
      theController.getCommand();
      string print_msg = theController.sendCommand(theGame);
      theController.requestDisplay(theGame, print_msg);
      if (theGame.gameOver()) {
        break;
      }
      
    }
    catch (Invalid_behave& ib) {
      cout << ib.what() << endl;
      continue;
    }
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
}
*/
