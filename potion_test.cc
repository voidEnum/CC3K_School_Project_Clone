#include "player.h"
#include "potion.h"

#include <iostream>
#include <memory>

using namespace std;

int main() {

  shared_ptr<Potion> RH1 = make_shared<Potion_RH>();
  shared_ptr<Potion> PH1 = make_shared<Potion_PH>();

  cout << "RH1 is Revealed returns : " << RH1->isRevealed() << endl;
  cout << "PH1 is Revealed returns : " << PH1->isRevealed() << endl;
  RH1->reveal();
  cout << "RH1 is Revealed now returns: " << RH1->isRevealed() << endl;
  cout << "PH1 is Revealed now returns: " << PH1->isRevealed() << endl;

  shared_ptr<Potion> RH2 = make_shared<Potion_RH>();

  cout << "RH2 is Revealed returns : " << RH2->isRevealed() << endl;

  shared_ptr<Player> player = make_shared<Player>("player");
  cout << "player's hp is " << player->getHp() << endl;
  player->useEntity(*RH1);
  cout << "after using RH1 player's hp is " << player->getHp() << endl;
  player->useEntity(*PH1);
  cout << "after using PH1 player's hp is " << player->getHp() << endl;
  cout << "PH1 is Revealed now returns: " << PH1->isRevealed() << endl;
}
