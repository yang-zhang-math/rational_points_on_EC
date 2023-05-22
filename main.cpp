#include <iostream>
#include "rational.h"

int main(void) {
    integer a("114514");
    integer b("-1919810");
    integer c=a+b;
    integer d=a-b;
    integer e=a*b;
    c.print_hex(); std::cout<<std::endl;
    d.print_hex(); std::cout<<std::endl;
    e.print_hex(); std::cout<<std::endl;
    return 0;
}
