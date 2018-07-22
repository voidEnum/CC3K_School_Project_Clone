#include "shade.h"

Shade::Shade(): Player("Shade", 125, 25, 25) {}

int Shade::finalScore() {
  return (getGold() * 3) / 2;
}
