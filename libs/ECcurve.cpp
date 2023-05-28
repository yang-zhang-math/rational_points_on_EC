/**Yang Zhang 28.05.2023
 * This is a file in the project rational_points_on_EC
 * https://github.com/yang-zhang-math/rational_points_on_EC
 * the struct of points and lines and the class of elliptic curves
 * Licensed under GNU General Public License v3.0
 */

#include "rational.h"
#include "ECcurve.h"

void ec::init(bigrat A,bigrat B,bigrat C,bigrat D,bigrat E,bigrat F,bigrat G,bigrat H,bigrat I,bigrat J)
{
    a=A;
    b=B;
    c=C;
    d=D;
    e=E;
    f=F;
    g=G;
    h=H;
    i=I;
    j=J;
}

bool ec::is_pt_on_curve(point pt)
{
    //compute all quadric terms
    bigrat X_sqr=bigrat_a_exp_with_n(pt.X, 2);
    bigrat Y_sqr=bigrat_a_exp_with_n(pt.Y, 2);
    bigrat X_Y=pt.X*pt.Y;

    //compute all cubic terms
    bigrat X_cub= X_sqr*pt.X;
    bigrat Y_cub= Y_sqr*pt.Y;
    bigrat X_sqr_Y= X_sqr*pt.Y;
    bigrat X_Y_sqr= pt.X*Y_sqr;

    //check whether aX^3+bX^2Y+cXY^2+dY^3+eX^2+fXY+gY^2+hX+iY+j=0
    bigrat result=(a*X_cub)+(b*X_sqr_Y)+(c*X_Y_sqr)+(d*Y_cub)+(e*X_sqr)+(f*X_Y)+(g*Y_sqr)+(h*pt.X)+(i*pt.Y)+j;
    return result.is_zero();
}

line ec::tangent_at_pt(point pt)
{
    //take the full differential of both sides, we get
    //(3a*X^2+2b*XY+c*Y^2+2e*X+f*Y+h)dx+(b*X^2+2c*XY+3d*Y^2+f*X+2g*Y+i)dy=0
    //If we denote the expression in the first bracket with u, in the second bracket with v
    //Then the tangent at pt will be u_0*x+v_0*y+k_0=0, where u_0 and v_0 are u and v evaluated at pt
    //k_0 can then be computed by evaluating the point to the line equation

    //compute all quadric terms
    bigrat X_sqr=bigrat_a_exp_with_n(pt.X, 2);
    bigrat Y_sqr=bigrat_a_exp_with_n(pt.Y, 2);
    bigrat X_Y=pt.X*pt.Y;

    //compute all cubic terms
    bigrat X_cub= X_sqr*pt.X;
    bigrat Y_cub= Y_sqr*pt.Y;
    bigrat X_sqr_Y= X_sqr*pt.Y;
    bigrat X_Y_sqr= pt.X*Y_sqr;

    //take 2 and 3 as bigrat numbers;
    bigrat bigrat_two(2,1);
    bigrat bigrat_three(3,1);

    line ans;

    //compute u_0 and v_0;
    ans.u=(bigrat_three*a*X_sqr)+(bigrat_two*b*X_Y)+(c*Y_sqr)+(bigrat_two*e*pt.X)+(f*pt.Y)+(h);
    ans.v=(b*X_sqr)+(bigrat_two*c*X_Y)+(bigrat_three*d*Y_sqr)+(f*pt.X)+(bigrat_two*g*pt.Y)+i;

    //compute k_0;
    ans.k=ans.u*pt.X+ans.v*pt.Y;
    ans.k.negate_self();

    return ans;
}

point ec::third_intersection_point(line ln, point pt)
{
    point ans;

    //if the u and v in tangent line are zero, that means we get a singular point, and we abort
    if(ln.v.is_zero() and ln.u.is_zero()){
        std::cout<<"Encounter a singular point, iteration failed";
        abort();
    }
    //if ln.v!=0, i.e. the line is not vertical, do the following computation
    else if(!(ln.v.is_zero())){
        //normalize the tangent line (divide the equation by v) to be ux+y+k=0
        ln.u.divide_with(ln.v);
        ln.k.divide_with(ln.v);
        ln.v.init(1,1);
        //compute u^2 and u^3;
        bigrat u_sqr= bigrat_a_exp_with_n(ln.u, 2);
        bigrat u_cub= bigrat_a_exp_with_n(ln.u, 3);

        //get the denominator of the negative sum of x coordinates of all three intersection points
        //which is just the denominator coefficient of X^2, namely a-bu+cu^2-du^3
        //the derivation of this expression can be found in computation.tex and computation.pdf
        bigrat neg_root_sum_denom= a-b*ln.u+c*u_sqr-d*u_cub;
        //if the denominator is zero, it means that the third intersection point is the point of infinity
        //and we abort the function
        if(neg_root_sum_denom.is_zero()){
            std::cout<<"Intersection at infinity point, iteration failed";
            abort();
        }

        //take 2 and 3 as bigrat numbers;
        bigrat bigrat_two(2,1);
        bigrat bigrat_three(3,1);
        //get the numerator of the negative sum of x coordinates of all three intersection points
        //which is just the numeratorcoefficient of X^2, namely -bk+2cuk-3du^2k+e-fu+gu^2
        //the derivation of this expression can be found in computation.tex and computation.pdf
        bigrat neg_root_sum_num= (b*ln.k).negation()+bigrat_two*c*ln.u*ln.k-bigrat_three*d*u_sqr*ln.k+e-f*ln.u+g*u_sqr;

        //get the sum of x coordinates of all three intersection points
        bigrat neg_root_sum =neg_root_sum_num/neg_root_sum_denom;

        //since neg_root_sum=-pt.X-pt.X- (X coordinate of new point), adding pt.X by twice and we get the negated X coordinate
        ans.X=neg_root_sum+pt.X+pt.X;
        ans.X.negate_self();
        //compute y=-ux-k
        ans.Y= ln.u*ans.X+ln.k;
        ans.Y.negate_self();

    //if u!=0 but v=0, we swap the coordinate and compute the result
    }else if(!(ln.v.is_zero())){
        //get the symmetric curve ,tangent line and point
        ec sym_curve(d,c,b,a,g,f,e,i,h,j);
        line sym_ln;
        sym_ln.u=ln.v;
        sym_ln.v=ln.u;
        sym_ln.k=ln.k;
        point sym_pt;
        sym_pt.X=pt.Y;
        sym_pt.Y=pt.X;

        //compute the symmetric ans, and then swap x and y
        ans=sym_curve.third_intersection_point(sym_ln,sym_pt);
        std::swap(ans.X,ans.Y);
    }
    
    return ans;
}