#ifndef MYMESH
#define MYMESH

#include "Mesh.h"
#include "Affine.h"

class MyMesh : public Mesh {
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
    static const Point vertices[11];
    static const Face faces[7];
    static const Edge edges[13];
};


inline
int MyMesh::VertexCount(void) {
  return sizeof(vertices)/sizeof(vertices[0]);
}


inline
Point MyMesh::GetVertex(int i) {
  return vertices[i];
}


inline
Vector MyMesh::Dimensions(void) {
  return Vector (4, 4);
}


inline
Point MyMesh::Center(void) {
  return Point(2,2);
}


inline
int MyMesh::FaceCount(void) {
  return sizeof(faces) / sizeof(faces[0]);
}


inline
Mesh::Face MyMesh::GetFace(int i) {
  return faces[i];
}


inline
int MyMesh::EdgeCount(void) {
  return sizeof(edges) / sizeof(edges[0]);
}


inline
Mesh::Edge MyMesh::GetEdge(int i) {
  return edges[i];
}


#endif
