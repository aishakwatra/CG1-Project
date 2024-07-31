#include "DrawLineMidpoint.h"


//return absolute value

int abs(int num) {
    return (num < 0) ? -num : num;
}



void DrawLineMidpoint(Raster &r, int x1, int y1, int x2, int y2){

    int dx = x2 - x1;
    int dy = y2 - y1;

    int x = x1;
    int y = y1;

    bool absoluteM = abs(dy) <= abs(dx); //true for more than or equal to 1

    int D1;

    r.GotoPoint(x1, y1);

    r.WritePixel();

    if (dx >= 0 && dy >= 0 && absoluteM) {

        //CASE 1

        D1 = dx - 2 * dy;

        while (x < x2) {

            if (D1 >= 0) {
                D1 += -2 * dy;

            }
            else {
                D1 += 2 * (dx - dy);
                y++;
            }

            x++;

            r.GotoPoint(x, y);
            r.WritePixel();

        }


    }
    else if (dx >= 0 && dy >= 0 && !absoluteM) {

        //CASE 2

        D1 = 2 * dx - dy;

        while (y < y2) {

            if (D1 >= 0) {

                D1 += 2 * (dx - dy);
                x++;

            }
            else {

                D1 += 2 * dx;

            }

            y++;

            r.GotoPoint(x, y);
            r.WritePixel();

        }


    }
    else if (dx >= 0 && dy < 0 && absoluteM) {

        //CASE 3

        D1 = -(dx + 2 * dy);

        while (x < x2) {

            if (D1 >= 0) {
                D1 += -2 * (dx + dy);
                y--;

            }
            else {
                D1 += -2 * dy;

            }

            x++;

            r.GotoPoint(x, y);
            r.WritePixel();

        }
        

    }
    else if (dx >= 0 && dy < 0 && !absoluteM) {

        //CASE 4

        D1 = 2 * dx + dy;

        while (y > y2) {

            if (D1 >= 0) {

                D1 += 2 * (dx + dy);
                x++;
                

            }
            else {

                D1 += (2 * dx);
                
            }

            y--;

            r.GotoPoint(x, y);
            r.WritePixel();


        }
        

    }
    else if (dx < 0 && dy >= 0 && absoluteM) {

        //CASE 5

        D1 = -dx - (2 * dy);

        while (x > x2) {

            if (D1 >= 0) {

                D1 += -2 * dy;

            }
            else {

                D1 += -2 * (dx + dy);
                y++;
            }

            x--;

            r.GotoPoint(x, y);
            r.WritePixel();

        }


    }
    else if (dx < 0 && dy >= 0 && !absoluteM) {

        //CASE 6
        
        D1 = -2 * dx - dy;

        while (y < y2) {

            if (D1 >= 0) {

                D1 += -2 * (dx + dy);
                x--;

            }
            else {

                D1 += -2 * dx;

            }

            y++;

            r.GotoPoint(x, y);
            r.WritePixel();

        }
        

    }
    else if (dx < 0 && dy < 0 && absoluteM) {

        //CASE 7

        D1 = dx - 2 * dy;

        while (x > x2) {

            if (D1 >= 0) {

                D1 += 2 * (dx - dy);
                y--;

            }
            else {

                D1 += -2 * dy;

            }

            x--;

            r.GotoPoint(x, y);
            r.WritePixel();
        }



    }
    else if (dx < 0 && dy < 0 && !absoluteM) {

        //CASE 8

        D1 = 2 * dx - dy;

        while (y > y2) {

            if (D1 >= 0) {

                D1 += 2 * dx;

            }
            else {

                D1 += 2 * (dx - dy);

                x--;

            }

            y--;

            r.GotoPoint(x, y);
            r.WritePixel();

        }


    }

    
} 




