# Rational Point on Elliptic Curves

last update: 23.05.2023
Author:Yang Zhang

This is an open-source C++ algorithm to compute Q-rational points on an elliptic curve defined over the field Q. To support the algorithm, a library of integers with arbitrary length and rational numbers with arbitrarily long numerators and denominators is attached.

# Basic Description of the Algorithm
The user need to give the elliptic curve in Weierstrass form and a rational point to start. Then the algorithm computes the tangent line of the curve through the rational point. By Bezout's theorem, the tangent line intersects with the elliptic curve at at most three points, counting multiplicity. Since the tangent point is counted twice with multiplicity, the tangent line has to intersect with the elliptic curve at a third point by Vieta's formulas. We then do the same process again to the new rational point we get and iterate everything, which in good cases produce infinitely many rational points on the curve.

# Obstructions of the Algorithm
It might be possible that we reach a point again after several iterations. It might also be possible that we get a vertical line for tangent, which gives the origin of the curve as the new iteration point. Even worse, for some points, the tangent line will intersect with the elliptic curve at this point with multiplicity three, namely we cannot iterate anymore. (These points are called inflection points in algebraic geometry I believe.) We introduce a hash function hashing every point we get into C++ int, so that we can notice when we fall into circulations at once and break the cycle.

# Why arbitrarily long integers and rationals?
When computing the tangent line and the new point, the size of numerators and denominators will explode very fast. The C++ long long type can also not last even after three to four iterations in some bad cases. So we have to use arbitrarily long integers and rationals.

# License
GNU General Public License v3.0
