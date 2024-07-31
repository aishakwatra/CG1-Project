                                                                                                                                                                                                  #include "RasterUtilities.h"
using namespace std;
#include <iostream>
#include "RasterUtilities.h"

// Custom floor function for float values
int customFloor(float x) {

	return static_cast<int>(x);
	
}

// Custom ceiling function for float values
int customCeil(float x) {

	return static_cast<int>(x + 0.9999999999f);

}

void FillTriangle(Raster& r, const Point& P, const Point& Q, const Point& R) {

	//ORDER VERTICES - SMALLEST TO LARGEST

	// Pointers to vertices
	const Point* bottom = &P;
	const Point* mid = &Q;
	const Point* top = &R;

	// Order pointers based on y-coordinate
	if (bottom->y > mid->y) {
		const Point* temp = bottom;
		bottom = mid;
		mid = temp;
	}
	if (mid->y > top->y) {
		const Point* temp = mid;
		mid = top;
		top = temp;
	}
	if (bottom->y > mid->y) {
		const Point* temp = bottom;
		bottom = mid;
		mid = temp;
	}


	
	// Inverse slope calculations

	float invM12 = (Hcoords::Near(mid->y, bottom->y)) ? 0.0f : (float)(mid->x - bottom->x) / (mid->y - bottom->y);
	float invM13 = (Hcoords::Near(top->y, bottom->y)) ? 0.0f : (float)(top->x - bottom->x) / (top->y - bottom->y);
	float invM23 = (Hcoords::Near(top->y, mid->y)) ? 0.0f : (float)(top->x - mid->x) / (top->y - mid->y);

	
	// Scanline conversion
	for (int y = customCeil(bottom->y); y <= customFloor(top->y); ++y) {

		float xLeft, xRight;

		if (y <= mid->y) {

			// Bottom half of the triangle

			xLeft = bottom->x + (invM13 * (y - bottom->y));
			xRight = bottom->x + (invM12 * (y - bottom->y));


		}
		else {
			// Top half of the triangle
			xLeft = mid->x + (invM23 * (y - mid->y));
			xRight = bottom->x + (invM13 * (y - bottom->y));
		}

		
		// Swap left and right if in the wrong order
		if (xLeft > xRight) {
			float temp = xLeft;
			xLeft = xRight;
			xRight = temp;
		}

		// Loop from min to max to draw pixels

		for (int x = customCeil(xLeft); x <= customFloor(xRight); x++) {
			
			r.GotoPoint(x, y);
			r.WritePixel();

		}


	}


}

