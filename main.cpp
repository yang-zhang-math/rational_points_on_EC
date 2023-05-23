#include <iostream>
#include "rational.h"

int main(void) {
    bigint a("11919810");
    bigint b("114514");
    bigint c=a+b;
    bigint d=a-b;
    bigint e=a*b;
    bigint f=a/b;
    bigint g=a%b;
    bigint h=bigint_gcd(a,b);
    bigint i=bigint_lcm(a,b);
    c.print_hex(); std::cout<<std::endl;
    d.print_hex(); std::cout<<std::endl;
    e.print_hex(); std::cout<<std::endl;
    f.print_hex(); std::cout<<std::endl;
    g.print_hex(); std::cout<<std::endl;
    h.print_hex(); std::cout<<std::endl;
    i.print_hex(); std::cout<<std::endl;
    return 0;
}
