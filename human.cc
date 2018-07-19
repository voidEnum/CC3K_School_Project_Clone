#include "human.h"
#include <iostream>

using namespace std;

Human::Human(shared_ptr<Cell> cellptr): 
   Enemy{cellptr, "H", 140, 20, 20} {}

