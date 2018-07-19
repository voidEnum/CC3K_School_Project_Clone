#include "dwarf.h"

#include <iostream>

using std::shared_ptr;

Dwarf::Dwarf(shared_ptr<Cell> cellptr): 
   Enemy{cellptr, "W", 100, 20, 30} {}
