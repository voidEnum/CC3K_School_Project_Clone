#include "cell.h"

#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"

#include <iostream>

using namespace std;

Cell::Cell(size_t r, size_t c): r{r}, c{c} {}

void Cell::setPiece(Colour colour) {
  this->colour = colour;
  setState({StateType::NewPiece, colour, Direction::N});
  // Direction of the newly placed piece does not matter
  notifyObservers();
  // After all the notifications are resolved, set the
  // state type of the cell to reply. Direction does not matter.
  setState({StateType::Reply, colour, Direction::N});
}

void Cell::toggle() {
  switch(colour) {
    case Colour::NoColour :                               break;
    case Colour::Black    : this->colour = Colour::White; break;
    case Colour::White    : this->colour = Colour::Black; break;
  }
}

// Precondtions: Can only be called by an observer cell.
// Observer cells should all be neighbours to this cell.
// Returns the direction that the caller is in in relation
// to this current cell.
Direction Cell::fromWhere(Subject<Info, State> &whoFrom) const {
  
  int dir = 0;
  Info whoInfo = whoFrom.getInfo();
  if (whoInfo.row < this->r) {
    dir -= 1;
  }else if (whoInfo.row > this->r) {
    dir += 1;
  }
  if (whoInfo.col < this->c) {
    dir -= 4;
  }else if (whoInfo.col > this->c) {
    dir += 4;
  }

  switch (dir) {
    case -5      :  return Direction::NW;
    case -4      :  return Direction::W;
    case -3      :  return Direction::SW;
    case -1      :  return Direction::N;
    case 1       :  return Direction::S;
    case 3       :  return Direction::NE;
    case 4       :  return Direction::E;
    case 5       :  return Direction::SE;
    default      :  return Direction::N; 
    // Default to north if calculation fails for some reason
  }
}

void Cell::notify(Subject<Info, State> &whoFrom) {
  // If the current cell does not have a piece in it, it does not
  // need to respond to state changes. Do nothing and return.
  if (colour == Colour::NoColour) {
    return;
  }

  // If this cell currently has the Statetype NewPiece, it has just been placed
  // Do not reply or relay any requests. Do nohting and return.
  if (getState().type == StateType::NewPiece) {
    return;
  }
  
  // Stores a copy of the callers state
  State s = whoFrom.getState();

  // Stores the direction of the caller in relation to this Cell.
  // Used for determining if Cells are in straight lines
  Direction fromDir = fromWhere(whoFrom);

  if (s.type == StateType::NewPiece) {
    if (colour == s.colour) {
      setState({StateType::Reply, s.colour, fromDir});
      notifyObservers();
    }else {
      setState({StateType::Relay, s.colour, fromDir});
      notifyObservers();
    }
  }else if (s.type == StateType::Relay) {
    // The new piece is in the same direction as the piece that notified you.
    if (fromDir == s.direction) {
      if (colour == s.colour) {
        setState({StateType::Reply, s.colour, s.direction});
        notifyObservers();
      } else {
        setState({StateType::Relay, s.colour, s.direction});
        notifyObservers();
      }
    }
  } else { // s.type == StateType::Reply
    bool fromOppDir;  // Is the notifing piece from the opposite direction
                      // of the new piece
    switch (fromDir) {
      case Direction::N  : fromOppDir = (s.direction == Direction::S);  break;
      case Direction::NE : fromOppDir = (s.direction == Direction::SW); break;
      case Direction::E  : fromOppDir = (s.direction == Direction::W);  break;
      case Direction::SE : fromOppDir = (s.direction == Direction::NW); break;
      case Direction::S  : fromOppDir = (s.direction == Direction::N);  break;
      case Direction::SW : fromOppDir = (s.direction == Direction::NE); break;
      case Direction::W  : fromOppDir = (s.direction == Direction::E);  break;
      case Direction::NW : fromOppDir = (s.direction == Direction::SE); break;
      default            : fromOppDir = false;
    }
    if (fromOppDir) {
      if (colour!= s.colour) {
        toggle();
        setState({StateType::Reply, s.colour, s.direction});
        notifyObservers();
      }
    }
  }
}

Info Cell::getInfo() const {
  return {r, c, colour};
}
