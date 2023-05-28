# Rational Point on Elliptic Curves

last update: 28.05.2023
Author:Yang Zhang

This is an open-source C++ algorithm to compute Q-rational points on an elliptic curve defined over the field Q. To support the algorithm, a library of integers with arbitrary length and rational numbers with arbitrarily long numerators and denominators is attached.

# Basic Description of the Algorithm
The user need to give a smooth elliptic curve and a rational point to start. Then the algorithm computes the tangent line of the curve through the rational point. By Bezout's theorem, the tangent line intersects with the elliptic curve at at most three points, counting multiplicity. Since the tangent point is counted twice with multiplicity, the tangent line has to intersect with the elliptic curve at a third point by Vieta's formulas. We then do the same process again to the new rational point we get and iterate everything, which in good cases produce infinitely many rational points on the curve.

# Obstructions of the Algorithm
It might be possible that we reach a point again after several iterations. Even worse, for some points, the tangent line will intersect with the elliptic curve at this point with multiplicity three, namely we cannot iterate anymore. (These points are called inflection points in algebraic geometry I believe.) We introduce a hash function hashing every point we get into C++ int, so that we can notice when we fall into circulations at once and break the cycle.

# Why arbitrarily long integers and rationals?
When computing the tangent line and the new point, the size of numerators and denominators will explode very fast. The C++ long long type can also not last even after three to four iterations in some bad cases. So we have to use arbitrarily long integers and rationals.

# Then why not BIGNUM in OpenSSL?
I don't like it. I hope to make the program as light weight and easy to use as possible. It may take hours for C++ beginners to set up their own environment with OpenSSL. A majority of pure mathematicians is not familiar with C++ and OpenSSL, and I just hope that they can use it directly with a simple C++ compiler.

# How to use?
If you have a C++ building environment with CMake, then just download the whole repository and build the main.cpp. You will find an executable file in the folder build <br />
If you do not have a CMake, then copy all the .h and .cpp files in the folder libs to the same directory of main.cpp, and compile main.cpp with any simple C++ compiler.

# License
GNU General Public License v3.0
