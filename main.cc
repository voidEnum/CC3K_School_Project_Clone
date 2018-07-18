#include <iostream>
#include <string>
#include "grid.h"

using namespace std;

int main() {

  Grid grid;

  try {
    grid.init("maps/basicFloor.txt", 1);
  } catch (MyMapNotFoundException e) {
    cout << e.what() << endl;
    return -1;
  }

  cout << grid;


}
