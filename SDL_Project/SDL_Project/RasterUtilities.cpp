#include "RasterUtilities.h"

void FillRect(Raster& r, int x, int y, int width, int height){

    // Start at the specified coordinates
    r.GotoPoint(x, y);

    // Fill the rectangle using IncrementX and IncrementY
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            r.WritePixel();
            r.IncrementX();
        }
        r.GotoPoint(x, y + i + 1);
    }

}

void DrawRect(Raster& r, int x, int y, int width, int height){
    
    // Start at the specified coordinates
    r.GotoPoint(x, y);

    // Fill the rectangle using IncrementX and IncrementY
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                
                r.WritePixel();
                
            }
            
            r.IncrementX();

        }

        r.GotoPoint(x, y + i + 1);
    }

}