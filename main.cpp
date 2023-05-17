#include <iostream>
#include "rational.h"

int main(void) {
    integer a("-1");
    integer b("1000000");
    a.add_with(b);
    a.print_hex();
    return 0;
}
