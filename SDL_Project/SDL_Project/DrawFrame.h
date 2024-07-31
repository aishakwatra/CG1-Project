// cs200final_proj.h
// cs200 6/14

#ifndef CS200FINAL_PROJ_H
#define CS200FINAL_PROJ_H

#include "Raster.h"
#include "RasterUtilities.h"
#include "Camera.h"
#include "Mesh.h"
#include "SquareMesh.h"
#include "MyMesh.h"
#include "Clip.h"

#include "DrawLineMidpoint.h"


// -------------- FrameBuffer Function --------------
void InitFrame(int width, int height);
void DrawFrame(Raster& r, double dt, int cam_num);


struct color { int r, g, b; };

void DrawMesh(Raster& r, Mesh* m, const Affine& A, const color& meshColor, const int& cam_num);
float frand(float a = 0, float b = 1);
void DrawSquareBorder(Raster& r, std::vector<Point>& clippedPoints, Mesh* m, const color& edgeColor);
void DrawMyMeshEdge(Raster& r, Mesh* mesh, const Affine& A, const color& meshColor, const int& cam_num);
void DrawGrid(Raster& r, const Affine& worldToNDC, const int& cam_num);
int GetGrayScale(int r, int g, int b);


#endif

