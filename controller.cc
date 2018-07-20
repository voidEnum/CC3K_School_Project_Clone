#include "controller.h"

#include "game.h"

Controller::Controller(std::istream &i): in{i}  {}

void Controller::getCommand() {
  std::getline(in, toSend);
}

void Controller::sendRace(Game &g) {
  g.startRound(toSend);
}

void Controller::sendCommand(Game &g) {
  g.processTurn(toSend);
}

void Controller::requestDisplay(Game &g) {
  g.print();
}
