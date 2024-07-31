#include "MyMesh.h"

const Point MyMesh::vertices[11]
  = { Point(2,0), Point(4,2), Point(3.5f,2.5f),  Point(3.5f,4), Point(3,3), Point(2.5f,3), 
	Point(1.5f,3), Point(1,3), Point(0.5f,2.5f), Point(0.5f,4) , Point(0,2) };


const Mesh::Face MyMesh::faces[7]
  = { Face(0,7,10), Face(0,4,7), Face(0,1,4), Face(2,3,4), Face(4,3,5), Face(7,6,9), Face(7,9,8) };


const Mesh::Edge MyMesh::edges[13]
  = { Edge(0,1), Edge(0,4), Edge(0,7), Edge(0,10), Edge(1,4), 
	Edge(4,7), Edge(7,10), Edge(8,9), Edge(7,9), Edge(6,9), 
	Edge(5,3), Edge(4,3), Edge(2,3) };

