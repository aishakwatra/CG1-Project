#include "HalfPlane.h"

float dot(const Hcoords& p, const Point& Q){

    return (p.x * Q.x) + (p.y * Q.y) + (p.w * Q.w);

}

Hcoords HalfPlane(const Point& A, const Point& B, const Point& P){

    Vector AB(B.x - A.x, B.y - A.y);


    Hcoords H1(-AB.y, AB.x, 0);
    Hcoords H2(AB.y, -AB.x, 0);
    
    float c = - (A.x * H1.x) - (A.y * H1.y);

    H1.w = c;
    H2.w = -c;

    if(dot(H1, P) < 0){
        return H1;
    } else if (dot(H2, P) < 0){
        return H2;
    }

}


Interval ClipSegment(const Hcoords& p, const Point& P, const Point& Q){

    //p - Half plane coordinates
    //P & Q form line segment

    Interval I;

    float HP = dot(p, P);
    float HQ = dot(p, Q);

    if (HP >= 0 && HQ >= 0) { //half plane completely outside of line segment
        
        I = Interval(1.0f, 0);

    } else if (HP < 0 && HQ < 0) { // whole line segmant inside halfplane 
        
        I = Interval();
        
    } else if (HP < 0 && HQ >= 0) {

        //time interval from t=0 at P
        //compute interval [a,b]

        float t = HP/(HP-HQ);
        
        I.bgn = 0;
        I.end = t;

    } else { //(HP >= 0 && HQ < 0)

        float t = HP / (HP - HQ);
        I.bgn = t;
        I.end = 1.0f;

    }

    return I;

}

