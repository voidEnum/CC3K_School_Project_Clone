#include "posn.h"

bool operator==(const Posn &p1, const Posn &p2) {
  return (p1.r == p2.r && p1.c == p2.c);
}

