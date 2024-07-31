//Aisha Kwatra 65360501808

#include "Affine.h"

Hcoords::Hcoords() : x(0.0f), y(0.0f), w(0.0f){}

Hcoords::Hcoords(float X, float Y, float W) : x(X), y(Y), w(W){}

Point::Point(void) : Hcoords(0.0f, 0.0f, 1.0f){}

Point::Point(float X, float Y): Hcoords(X, Y, 1.0f){}

Vector::Vector(void): Hcoords(0.0f, 0.0f, 0.0f){}

Vector::Vector(float X, float Y): Hcoords(X, Y, 0.0f){}

bool Vector::Normalize(void){

    float length = sqrt((x*x) + (y*y));

    if(length < 1e-5f){
        return false;
    }

    x = x/length;
    y = y/length;
    w = 0.0f; //0.0f indicating it is a vector not a point

    return true;
}


Affine::Affine(void){

    row[0] = Hcoords(1.0f, 0.0f, 0.0f);
    row[1] = Hcoords(0.0f, 1.0f, 0.0f);
    row[2] = Hcoords(0.0f, 0.0f, 1.0f);

}

Affine::Affine(const Vector& Lx, const Vector& Ly, const Point& disp){

    //Lx represents the 1st column of the matrix
    //Ly represents the 2nd column 
    //disp represents the 3rd column

    //Lx and Ly represent the scaling and rotation components
    //disp represents the translation component

    row[0] = Hcoords(Lx.x, Ly.x, disp.x);
    row[1] = Hcoords(Lx.y, Ly.y, disp.y);
    row[2] = Hcoords(Lx.w, Ly.w, disp.w);

}

Hcoords operator+(const Hcoords& u, const Hcoords& v){
    Hcoords result;
    result.x = u.x + v.x;
    result.y = u.y + v.y;
    result.w = u.w + v.w;
    return result;
}

Hcoords operator-(const Hcoords& u, const Hcoords& v){
    Hcoords result;
    result.x = u.x - v.x;
    result.y = u.y - v.y;
    result.w = u.w - v.w;
    return result;
}

Hcoords operator-(const Hcoords& v){
    Hcoords result;
    result.x = -v.x;
    result.y = -v.y;
    result.w = -v.w;
    return result;
}

Hcoords operator*(float r, const Hcoords& v){
    Hcoords result;
    result.x = r * v.x;
    result.y = r * v.y;
    result.w = r * v.w;
    return result;
}

Hcoords operator*(const Affine& A, const Hcoords& v){
    Hcoords result;

    for(int i = 0; i < 3; i++){

        result[i] = 0.0f;

        for(int j = 0; j < 3 ; j++){
            result[i] += A.row[i][j] * v[j];
        }
    }

    return result;

}


Affine operator*(const Affine& A, const Affine& B){

    Affine result;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3 ; j++){

            result.row[i][j] = 0.0f;

            for(int k = 0; k < 3; k++){
                result.row[i][j] += (A.row[i][k] * B.row[k][j]);
            }
        }
    }

    return result;

}

float dot(const Vector& u, const Vector& v){

    float result = 0.0f;
    for(int i = 0; i < 2; i++){
        result += (u[i]*v[i]);
    }
    return result;
}


float abs(const Vector& v){
    float length = sqrt((v.x * v.x) + (v.y * v.y));
    return length;
}


Affine Rot(float t){

    Affine result;

    result.row[0] = Hcoords(cos(t), -1*sin(t), 0.0f);
    result.row[1] = Hcoords(sin(t), cos(t), 0.0f);
    result.row[2] = Hcoords(0.0f, 0.0f, 1.0f);

    return result;

}

Affine Trans(const Vector& v){

    Affine result;

    result.row[0] = Hcoords(1.0f, 0.0f, v.x);
    result.row[1] = Hcoords(0.0f, 1.0f, v.y);
    result.row[2] = Hcoords(0.0f, 0.0f, 1.0f);

    return result;

}

Affine Scale(float r){

    Affine result;

    result.row[0] = Hcoords(r, 0.0f, 0.0f);
    result.row[1] = Hcoords(0.0f, r, 0.0f);
    result.row[2] = Hcoords(0.0f, 0.0f, 1.0f);

    return result;

}

Affine Scale(float rx, float ry){

    Affine result;

    result.row[0] = Hcoords(rx, 0.0f, 0.0f);
    result.row[1] = Hcoords(0.0f, ry, 0.0f);
    result.row[2] = Hcoords(0.0f, 0.0f, 1.0f);

    return result;

}

Affine Inverse(const Affine& A) {

    Affine result;

    float determinant = (A.row[0][0] * A.row[1][1]) - (A.row[1][0] * A.row[0][1]);


    result.row[0] = Hcoords((A.row[1][1] / determinant), -(A.row[0][1] / determinant), (A.row[0][1] * A.row[1][2] - A.row[1][1] * A.row[0][2]) / determinant);
    result.row[1] = Hcoords( -(A.row[1][0] / determinant), (A.row[0][0] / determinant),  (A.row[1][0] * A.row[0][2] - A.row[0][0] * A.row[1][2]) / determinant);
    result.row[2] = Hcoords(0.0f, 0.0f, 1.0f);

    return result;

}

                                      