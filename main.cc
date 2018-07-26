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

