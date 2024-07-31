// Clip.h
// -- clip/cull with respect to a given convex polygon
// cs200 11/14

#ifndef CS200_CLIP_H
#define CS200_CLIP_H

#include <vector>
#include "Affine.h"
#include "HalfPlane.h"



class Clip {
  public:
    Clip(void);
    Clip(int n, const Point* clip_to_verts);
    bool operator()(Point& A, Point& B);
    bool operator()(std::vector<Point>& verts);
  private:
    std::vector<Hcoords> half_planes;
    std::vector<Point> temp_points;
};


#endif

