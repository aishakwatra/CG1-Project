#include "Clip.h"
#include <iostream>

Clip::Clip(void){

    Point topLeft = Point(-1.0f, 1.0f);
    Point topRight = Point(1.0f, 1.0f);
    Point bottomLeft = Point(-1.0f, -1.0f);
    Point bottomRight = Point(1.0f, -1.0f);

    half_planes.push_back(HalfPlane(bottomLeft, bottomRight, topLeft));
    half_planes.push_back(HalfPlane(topRight, bottomRight, bottomLeft));
    half_planes.push_back(HalfPlane(topLeft, topRight, bottomRight));
    half_planes.push_back(HalfPlane(bottomLeft, topLeft, topRight));

}

Clip::Clip(int n, const Point* clip_to_verts){

    for (int i = 0; i < n; ++i) {
        Point A = clip_to_verts[i];
        Point B = clip_to_verts[(i + 1) % n];
        Point C = clip_to_verts[(i + 2) % n];  // Use the 3rd point as a point in the plane
        half_planes.push_back(HalfPlane(A, B, C));
    }

}

bool Clip::operator()(Point& A, Point& B){

    //CLIP LINE SEGMENT TO POLYGON

   bool intersect = true;

    for ( Hcoords& halfplane : half_planes) {

        Interval I = ClipSegment(halfplane, A, B);
        if (I.IsEmpty())
        {
            intersect = false;
            continue;
        }

        A = A + I.bgn * (B - A);
        B = A + I.end * (B - A);

    }

    return intersect;

}

bool Clip::operator()(std::vector<Point>& verts){

    
    bool isIntersect = false;
    temp_points = verts;

    for(Hcoords& halfPlane: half_planes){

        std::vector<Point> result_verts;

        for(int i = 0; i < temp_points.size(); i++){

            Point& A = temp_points[i];
            int nextIndex = (i + 1) % temp_points.size(); //wrap around when at the last index
            Point& B = temp_points[nextIndex];

            Interval I = ClipSegment(halfPlane, A, B);

            if(I.IsEmpty()){

                continue;

            } else {
                
                Point P1 = A + I.bgn * (B - A);
                Point P2 = A + I.end * (B - A);

                if (I.bgn == 0.0f && I.end == 1.0f) //IN-IN: adds point B
                {
                    result_verts.push_back(P2);
                }
                else if (I.bgn == 0.0f) //IN-OUT: add intersection point
                {
                    result_verts.push_back(P2);
                }
                else if (I.end == 1.0f) //OUT-IN: intersection + B
                {
                    result_verts.push_back(P1);
                    result_verts.push_back(P2);
                }
            

                isIntersect = true;

            }

        }

        temp_points = result_verts;

    }

    verts = temp_points;
    temp_points.clear();
    return isIntersect; 


}