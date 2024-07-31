#include "DrawFrame.h"


int screenWidth;
int screenHeight;
float aspect;

// Unit Square centered ar origin

const int vertex_count = 4;
const Point vertices[vertex_count]
= { Point(0.5f,0.5f), Point(-0.5f,0.5f),
    Point(-0.5f,-0.5f), Point(0.5f,-0.5f) };
Point temp_verts[vertex_count];

const int face_count = 2;
const struct { int index1, index2, index3; }
faces[face_count] = { {0,1,2}, {0,2,3} };

const int edge_count = 4;
const struct { int index1, index2; }
edges[edge_count] = { 0,1, 1,2, 2,3, 3,0 };

//All abjects - 50 meshes and checkered grid
MyMesh myMesh;
SquareMesh squareMesh;

const int mesh_count = 50;
Affine myMeshTransformations[mesh_count];
float rotation_speeds[mesh_count];
color myMesh_colors[mesh_count];

const int square_count = 6;
const float sScale = 1.75f;


// CAMERA
// 0 = Stationary
// 1 = Moving
Camera camera[2];
const float cameraRotationSpeed = 0.4f;
Point cam_vertices[4];

Clip screenHalfPlanes;
Clip camHalfPlanes;

color edgeColor{ 0, 0, 0 };


int GetGrayScale(int r, int g, int b)
{
    float grayScale = 0.299 * r + 0.587 * g + 0.114 * b;
    return (int)grayScale;
}

float frand(float a, float b)
{
    return a + (b - a) * float(rand()) / float(RAND_MAX);
}


void InitFrame(int width, int height)
{
   
    screenWidth = width;
    screenHeight = height;

    aspect = float(width) / float(height);
    camera[0] = Camera(Point(0, 0), Vector(0, 1), aspect * 13, 13);
    camera[1] = Camera(Point(0, 0), Vector(0, 1), aspect * 5, 5);


    //initialize half planes for clipping region - screen

    Point screenPoints[4] = { Point(1, 1), Point(screenWidth - 1, 1), Point(screenWidth - 1, screenHeight - 1), Point(1, screenHeight - 1) };
    screenHalfPlanes = Clip(4, screenPoints);

    
    for (int i = 0; i < mesh_count; ++i)
    {
        float scale = frand(0.1f, 0.9f);
        myMeshTransformations[i] = Trans(Vector(frand(camera[0].Center().x - 5.0f, camera[0].Center().x + 5.0f), frand(camera[0].Center().y - 5.0f, camera[0].Center().y + 5.0f))) * Scale(scale);
        rotation_speeds[i] = frand(0.1f, 1.0f);
    }

    int* color = &(myMesh_colors[0].r);
    for (int i = 0; i < 3 * mesh_count; ++i)
        color[i] = 150 + rand() % 106;


}

/*-----------------------------------------------------------------------------------------------------------*/

//FUNCTIONS THAT RENDER THE CHECKERED BACKGROUND

void DrawSquareBorder(Raster& r, std::vector<Point>& clippedPoints, Mesh* m, const color& edgeColor) {

    // Set the edge color
    r.SetColor(edgeColor.r, edgeColor.g, edgeColor.b);

    for (int i = 1; i <= clippedPoints.size(); i++)
    {
        Point& A = clippedPoints[i - 1];
        Point& B = clippedPoints[i % clippedPoints.size()];
        DrawLineMidpoint(r, A.x, A.y, B.x, B.y);
    }

}

void DrawGrid(Raster& r, const Affine& worldToNDC, const int& cam_num) {


    Vector offset = Vector(sScale / 2.0f, sScale / 2.0f);
    Point center = Point(square_count * sScale / 2.0f, square_count * sScale / 2.0f);
    
    

    for (int i = 0; i < square_count; i++) {

        for (int j = 0; j < square_count; j++) {

            std::vector<Point> transformedPoints;

            Vector incrementSquare = Vector(Point(j * sScale, i * sScale) + offset - center);

            // Set Transform Matrix
            Affine B = worldToNDC * Trans(incrementSquare) * Scale(sScale) * Trans(Point(0, 0) - squareMesh.Center());

            for (int i = 0; i < squareMesh.VertexCount(); ++i)
            {
                transformedPoints.push_back(B * squareMesh.GetVertex(i));
            }

            color squareColor;
            if ((i + j) % 2 == 0) {
                squareColor = { 255,218,218 };
            }
            else {
                squareColor = { 218,252, 255 };
            }

            // Draw Square on each grid
            DrawMesh(r, &squareMesh, B, squareColor, cam_num);


            screenHalfPlanes(transformedPoints);
            color edgeColor = { 0, 0, 0 };
            DrawSquareBorder(r, transformedPoints, &squareMesh, edgeColor);


        }
    }


}

/*-----------------------------------------------------------------------------------------------------------*/


void DrawMesh(Raster& r, Mesh* mesh, const Affine& A, const color& meshColor, const int& cam_num) {

    std::vector<Point> transformedPoints(mesh->VertexCount());
    for (int i = 0; i < mesh->VertexCount(); ++i) {
        transformedPoints[i] = A * mesh->GetVertex(i);
    }

    for (int i = 0; i < mesh->FaceCount(); ++i) {
        Mesh::Face face = mesh->GetFace(i);

        std::vector<Point> greyPoints = {
            transformedPoints[face.index1],
            transformedPoints[face.index2],
            transformedPoints[face.index3]
        };

        std::vector<Point> coloredPoints = {
            transformedPoints[face.index1],
            transformedPoints[face.index2],
            transformedPoints[face.index3]
        };


        if (cam_num == 0) {

            //bool inScreenView = screenHalfPlanes(facePoints1);
            //bool inCameraView = camHalfPlanes(facePoints2);

            int grey = GetGrayScale(meshColor.r, meshColor.g, meshColor.b);

            if (screenHalfPlanes(greyPoints)) { //draw all grey pixels first - clip to screen cam 0

                r.SetColor(grey, grey, grey);

                for (int j = 2; j < greyPoints.size(); ++j) {

                    FillTriangle(r, greyPoints[0], greyPoints[j - 1], greyPoints[j]);

                }
            }

            if (screenHalfPlanes(coloredPoints) && camHalfPlanes(coloredPoints)) { //clip to screen and camera to draw colored pixels

                r.SetColor(meshColor.r, meshColor.g, meshColor.b);

                for (int j = 2; j < coloredPoints.size(); ++j) {

                    FillTriangle(r, coloredPoints[0], coloredPoints[j - 1], coloredPoints[j]);

                }

            }

        }
        else if (cam_num == 1) {

            // Apply total clipping for cam_num == 1
            if (screenHalfPlanes(coloredPoints) && camHalfPlanes(coloredPoints)) { //clip and draw only colored pixels

                r.SetColor(meshColor.r, meshColor.g, meshColor.b);

                for (int j = 2; j < coloredPoints.size(); ++j) {

                    FillTriangle(r, coloredPoints[0], coloredPoints[j - 1], coloredPoints[j]);

                }

            }
        }
    }

}


/*
void DrawMesh(Raster& r, Mesh* m, const Affine& A, const color& meshColor, const int& cam_num) {
    std::vector<Point> transformedPoints(m->VertexCount());
    for (int i = 0; i < m->VertexCount(); ++i) {
        transformedPoints[i] = A * m->GetVertex(i);
    }

    // Calculate grayscale color once, outside the loop.
    int grayScale = GetGrayScale(meshColor.r, meshColor.g, meshColor.b);

    for (int i = 0; i < m->FaceCount(); ++i) {
        Mesh::Face face = m->GetFace(i);
        std::vector<Point> facePoints = {
            transformedPoints[face.index1],
            transformedPoints[face.index2],
            transformedPoints[face.index3]
        };

        // Determine whether the face is inside or outside the camera view.
        bool isFaceInsideCamera = camHalfPlanes(facePoints);

        // Set the color for the entire face based on its position.
        color finalColor = isFaceInsideCamera ? meshColor : color{ grayScale, grayScale, grayScale };
        r.SetColor(finalColor.r, finalColor.g, finalColor.b);

        // Check if the face is within the screen view and render it.
        if (screenHalfPlanes(facePoints)) {
            for (int j = 2; j < facePoints.size(); ++j) {
                FillTriangle(r, facePoints[0], facePoints[j - 1], facePoints[j]);
            }
        }
    }
}

*/

void DrawMyMeshEdge(Raster& r, Mesh* mesh, const Affine& A, const color& meshColor, const int& cam_num) {

    std::vector<Point> transformedPoints(mesh->VertexCount());
    for (int i = 0; i < mesh->VertexCount(); ++i) {
        transformedPoints[i] = A * mesh->GetVertex(i);
    }

    for (int i = 0; i < mesh->FaceCount(); ++i) {

        Mesh::Face face = mesh->GetFace(i);

        std::vector<Point> edgePoints{

            transformedPoints[face.index1],
            transformedPoints[face.index2],
            transformedPoints[face.index3],

        };
        

        for (int j = 0; j < 3; j++) {

            Point& A = edgePoints[j];
            Point& B = edgePoints[(j + 1) % 3];

            r.SetColor(0, 0, 0);

            if (cam_num == 0) {

                if (screenHalfPlanes(A, B)) {

                    DrawLineMidpoint(r, A.x, A.y, B.x, B.y);

                }

            }

            else {

                if (camHalfPlanes(A, B) && screenHalfPlanes(A, B)) {

                    DrawLineMidpoint(r, A.x, A.y, B.x, B.y);

                }

            }

        }
        
    }

}

/*----------------------------------------------------------------------------------------------------------*/

void DrawFrame(Raster& r, double dt, int cam_num)
{
    
    //CLEAR SCREEN EVERY FRAME
    r.SetColor(255, 255, 255);
    for (int i = 0; i < screenHeight; i++){
        for (int j = 0; j < screenWidth; j++){
            r.GotoPoint(i, j);
            r.WritePixel();   
        }
    }

    //-----------------

    //Translate and rotate camera
    //Affine cameraMovement = Inverse(Rot(dt * 0.2f) * Trans(Vector(4.0f , 0.0f)));
    
    Affine WorldToNDC = CameraToNDC(camera[cam_num]) * WorldToCamera(camera[cam_num]);
  
    Affine NDCToWorld = Trans(Vector(screenWidth / 2, screenHeight / 2)) * Scale(screenWidth / 2, screenHeight / 2);

    Affine A = NDCToWorld * WorldToNDC;

    
    //Rotate
    camera[1].Rotate(cameraRotationSpeed * dt);
  

    //DRAW CHECKERED BACKGROUND
    DrawGrid(r, A , cam_num);

    // Rotating Object
    for (int i = 0; i < mesh_count; ++i) {

        myMeshTransformations[i] = myMeshTransformations[i] * Rot(dt * rotation_speeds[i]);
        Affine B = A * myMeshTransformations[i] * Trans(Point(0, 0) - myMesh.Center());

        DrawMesh(r, &myMesh, B, myMesh_colors[i], cam_num);
        DrawMyMeshEdge(r, &myMesh, B, edgeColor, cam_num);

    }

    if (cam_num == 0) {

        r.SetColor(255, 0, 0);

        Affine B = Trans(Vector(screenWidth / 2.0f, screenHeight / 2.0f)) * CameraToWorld(camera[1]) * Scale(screenWidth / 2.0f, screenHeight / 2.0f);

        for (int i = 0; i < vertex_count; ++i) {
            temp_verts[i] = B * vertices[i];
            cam_vertices[i] = temp_verts[i];
        }

        //draw rotating square for camera

        for (int k = 0; k < edge_count; ++k) {
            DrawLineMidpoint(r, temp_verts[edges[k].index1].x, temp_verts[edges[k].index1].y, temp_verts[edges[k].index2].x, temp_verts[edges[k].index2].y);
        }

    } else{
        
        Affine B = NDCToWorld * Scale(2.1f);
        for (int i = 0; i < vertex_count; ++i) {

            temp_verts[i] = B * vertices[i];
            cam_vertices[i] = temp_verts[i];

        }
        
    }

    camHalfPlanes = Clip(4, cam_vertices);

}







