/**Yang Zhang 28.05.2023
 * This is a file in the project rational_points_on_EC
 * https://github.com/yang-zhang-math/rational_points_on_EC
 * the struct of points and lines and the class of elliptic curves
 * Licensed under GNU General Public License v3.0
 */

#ifndef ECCURVE_H
#define ECCURVE_H

#include "rational.h"

// the struct of points
struct point
{
    bigrat X;
    bigrat Y;
};

// the struct of lines

struct line
{
    // aX+bY+c=0
    bigrat u;
    bigrat v;
    bigrat k;
};

class ec
{

private:
    // aX^3+bX^2Y+cXY^2+dY^3+eX^2+fXY+gY^2+hX+iY+j=0
    bigrat a, b, c, d, e, f, g, h, i, j;

public:
    // aX^3+bX^2Y+cXY^2+dY^3+eX^2+fXY+gY^2+hX+iY+j=0
    ec(bigrat A, bigrat B, bigrat C, bigrat D, bigrat E, bigrat F, bigrat G, bigrat H, bigrat I, bigrat J)
    {
        a = A;
        b = B;
        c = C;
        d = D;
        e = E;
        f = F;
        g = G;
        h = H;
        i = I;
        j = J;
    }

    // init function, aX^3+bX^2Y+cXY^2+dY^3+eX^2+fXY+gY^2+hX+iY+j=0
    // this does not check whether the curve is smooth!
    void init(bigrat A, bigrat B, bigrat C, bigrat D, bigrat E, bigrat F, bigrat G, bigrat H, bigrat I, bigrat J);

    // check whether a point (X,Y) is on the curve
    bool is_pt_on_curve(point pt);

    // computes the tangent line at pt
    line tangent_at_pt(point pt);

    // inputs the tangent line ln at point pt, returns the third intersection point of the tangent and the curve
    // the function does not check whether the ln is really the tangent at pt
    point third_intersection_point(line ln, point pt);
};

#endif