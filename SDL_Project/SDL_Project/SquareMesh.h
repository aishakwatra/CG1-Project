#pragma once


#include "Mesh.h"
#include "Affine.h"

class SquareMesh : public Mesh {
public:
    int VertexCount(void);
    Point GetVertex(int i);
    Vector Dimensions(void);
    float Height(void);
    Point Center(void);
    int FaceCount(void);
    Face GetFace(int i);
    int EdgeCount(void);
    Edge GetEdge(int i);
private:
    static const Point vertices[4];
    static const Face faces[2];
    static const Edge edges[4];
};


inline
int SquareMesh::VertexCount(void) {
    return 4;
}


inline
Point SquareMesh::GetVertex(int i) {
    return vertices[i];
}


inline
Vector SquareMesh::Dimensions(void) {
    return Vector(1, 1);
}


inline
Point SquareMesh::Center(void) {
    return Point(0.5f, 0.5f);
}


inline
int SquareMesh::FaceCount(void) {
    return 2;
}


inline
Mesh::Face SquareMesh::GetFace(int i) {
    return faces[i];
}


inline
int SquareMesh::EdgeCount(void) {
    return 4;
}


inline
Mesh::Edge SquareMesh::GetEdge(int i) {
    return edges[i];
}
