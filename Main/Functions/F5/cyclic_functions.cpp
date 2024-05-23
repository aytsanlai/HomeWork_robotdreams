#include "cyclic_functions.h"
#include <cmath>

namespace CyclicFunctions {
    const float PI = 3.14159265359;

    float getArea(float radius) {
        return PI * radius * radius;
    }

    float getCircumference(float radius) {
        return 2 * PI * radius;
    }
}

