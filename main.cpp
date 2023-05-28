/**Yang Zhang 28.05.2023
 * This is the main cpp in the project rational_points_on_EC
 * https://github.com/yang-zhang-math/rational_points_on_EC
 * Licensed under GNU General Public License v3.0
 */

#include <iostream>
#include "ECcurve.h"

//read a bigrat number from stdin stream, name is used to instruct the user, which can be NULL
bigrat input_bigrat(std::string name)
{
    std::string num,denom;
    if(!name.empty()){
        std::cout << "Input " << name << " in *HEXADECIMAL*" << std::endl;
    }
    std::cout << "Input numerator: ";
    std::cin >> num;
    std::cout << "Input denominator: ";
    std::cin >> denom;
    bigrat ans(num,denom);
    return ans;
}

//the instructing function
void compute_rational_points(void)
{
    std::cout   << "Raitonal Points on Elliptic Curves" << std::endl
                << "Last modified 28.05.2023" << std::endl
                << "The Github repository can be found on https://github.com/yang-zhang-math/rational_points_on_EC" <<std::endl
                << "Licensed under GNU General Public License v3.0" << std::endl;
    std::cout   << "To start with, input a plane cubic curve in hexadecimal." << std::endl
                << "Denote the curve with aX^3+bX^2Y+cXY^2+dY^3+eX^2+fXY+gY^2+hX+iY+j=0." << std::endl
                << "Follow the instruction to input from a to j" << std::endl;
    bigrat a=input_bigrat("a");
    bigrat b=input_bigrat("b");
    bigrat c=input_bigrat("c");
    bigrat d=input_bigrat("d");
    bigrat e=input_bigrat("e");
    bigrat f=input_bigrat("f");
    bigrat g=input_bigrat("g");
    bigrat h=input_bigrat("h");
    bigrat i=input_bigrat("i");
    bigrat j=input_bigrat("j");

    ec curve(a,b,c,d,e,f,g,h,i,j);

    //the loop forces the point to be on the curve
    point pt;
    bool flag=1;
    while(flag){
        std::cout   << "You still need to input a rational point on the curve in hexadecimal to start with." << std::endl
                    << "Denote the point with coordinate (X,Y)." << std::endl;
        bigrat X=input_bigrat("X");
        bigrat Y=input_bigrat("Y");

        pt.X=X;
        pt.Y=Y;
        flag= !curve.is_pt_on_curve(pt);
    }

    std::cout   << "How many rational points do you need?" << std::endl
                << "You can expect the calculation for the first five points to be finished in 24 hours." << std::endl
                << "Input the number in decimal:";
    int count;
    std::cin >> count;

    for(int i=1;i<=count;i++){
        pt=curve.third_intersection_point(curve.tangent_at_pt(pt),pt);
        std::cout << i << std::endl << ": X:" << std::endl;
        pt.X.print_hex();
        std::cout << "Y:" << std::endl;
        pt.Y.print_hex();
        std::cout   << "Double check result of whether the point is on the curve: "
                    << curve.is_pt_on_curve(pt) << std::endl;
    }
    std::cout << "Computation finished, you can turn off the program now.";
} 

int main(void)
{
    compute_rational_points();
    std::cout << "Press Enter to continue";
    getchar(); getchar();
    return 0;
}
