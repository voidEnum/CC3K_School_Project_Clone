#ifndef __POSN_H__
#define __POSN_H__

struct Posn {
  int r;
  int c;
};

bool operator==(const Posn &p1, const Posn &p2);
#endif
