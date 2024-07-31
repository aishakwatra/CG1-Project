// HalfPlane.h
// -- utilities for half-planes
// cs200 4/14

#ifndef CS200_HALFPLANE
#define CS200_HALFPLANE

#include "Affine.h"


float dot(const Hcoords& p, const Point& Q);

Hcoords HalfPlane(const Point& A, const Point& B, const Point& P);

struct Interval {
  float bgn, end;
  Interval(float a=0, float b=1) : bgn(a), end(b) { }
  bool IsEmpty(void) const { return bgn > end; }
};

Interval ClipSegment(const Hcoords& p, const Point& P, const Point& Q);


#endif

