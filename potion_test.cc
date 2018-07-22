#include "potion_rh.h"
#include "potion_ph.h"

#include <iostream>
#include <memory>

using namespace std;

int main() {

  shared_ptr<Potion_RH> RH1 = make_shared<Potion_RH>();
  shared_ptr<Potion_PH> PH1 = make_shared<Potion_PH>();

  cout << "RH1 is Revealed returns : " << RH1->isRevealed() << endl;
  cout << "PH1 is Revealed returns : " << PH1->isRevealed() << endl;
  RH1->reveal();
  cout << "RH1 is Revealed now returns: " << RH1->isRevealed() << endl;
  cout << "PH1 is Revealed now returns: " << PH1->isRevealed() << endl;

  shared_ptr<Potion_RH> RH2 = make_shared<Potion_RH>();

  cout << "RH2 is Revealed returns : " << RH2->isRevealed() << endl;

}
