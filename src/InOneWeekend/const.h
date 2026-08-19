#ifndef CONST_H
#define CONST_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

// usings
using std::make_shared;
using std::shared_ptr;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility fxns
inline double degress_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // return random double in [0,1)
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // return random double in [min,max)
    return min + (max-min) * random_double();
}

// headers
#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif