/**Yang Zhang 28.05.2023
 * This is a file in the project rational_points_on_EC
 * https://github.com/yang-zhang-math/rational_points_on_EC
 * test of the bigint class and bigrat class
 * Licensed under GNU General Public License v3.0
 */

#include "test.h"

// test the bigint class
void bigint_test()
{
    bigint a("1919810");
    bigint b("114514");
    bigint c = a + b;
    bigint d = a - b;
    bigint e = a * b;
    bigint f = a / b;
    bigint g = a % b;
    bigint h = bigint_gcd(a, b);
    bigint i = bigint_lcm(a, b);
    bigint j = bigint_a_exp_with_n(a, 1000);
    c.print_hex();
    std::cout << std::endl;
    d.print_hex();
    std::cout << std::endl;
    e.print_hex();
    std::cout << std::endl;
    f.print_hex();
    std::cout << std::endl;
    g.print_hex();
    std::cout << std::endl;
    h.print_hex();
    std::cout << std::endl;
    i.print_hex();
    std::cout << std::endl;
    j.print_hex();
    std::cout << std::endl;
}

// test the bigrat class
void bigrat_test()
{
    bigrat a(-1919810, 114514);
    bigrat b(114514, 1919810);
    bigrat c = a + b;
    bigrat d = a - b;
    bigrat e = a * b;
    bigrat f = a / b;
    bigrat g = bigrat_a_exp_with_n(a, 1000);
    c.print_hex();
    std::cout << std::endl;
    d.print_hex();
    std::cout << std::endl;
    e.print_hex();
    std::cout << std::endl;
    f.print_hex();
    std::cout << std::endl;
    g.print_hex();
    std::cout << std::endl;
}

// test the output using curve X^3+Y^3=1141
void ec_test(void)
{
    bigrat bigrat_zero(0, 1);
    bigrat bigrat_one(1, 1);
    bigrat bigrat_1141(-1141, 1);
    bigrat bigrat_20(20, 1);
    bigrat bigrat_19(-19, 1);
    ec curve(bigrat_one, bigrat_zero, bigrat_zero, bigrat_one, bigrat_zero, bigrat_zero, bigrat_zero, bigrat_zero, bigrat_zero, bigrat_1141);
    point pt;
    pt.X = bigrat_20;
    pt.Y = bigrat_19;
    for (int i = 0; i < 5; i++)
    {
        pt = curve.third_intersection_point(curve.tangent_at_pt(pt), pt);
        std::cout << i << ": X:" << std::endl;
        pt.X.print_hex();
        std::cout << "Y:" << std::endl;
        pt.Y.print_hex();
        std::cout << curve.is_pt_on_curve(pt) << std::endl;
    }
}