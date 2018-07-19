#include "dragon.h"
#include <iostream>

using namespace std;

Human::Human(shared_ptr<Cell> cellptr, shared_ptr<Cell> hoardptr): 
   Enemy{cellptr, hoardptr, "D", 150, 20, 20} {}

