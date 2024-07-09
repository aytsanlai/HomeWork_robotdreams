#include <iostream>
#include "Vector2d.h"

int main() {
    Vector2d testVec{ 1.2, 5.6 };
    std::cout << testVec << std::endl;

    Vector2d v1{ 2.0, 3.0 };
    Vector2d v2{ 1.0, 1.0 };
    Vector2d v3 = v1 + v2;
    std::cout << "Vector Addition: " << v3 << std::endl;

    Vector2d v4 = v1 - v2;
    std::cout << "Vector Subtraction: " << v4 << std::endl;

    std::cout << "Vector x: " << v3[0] << ", y: " << v3[1] << std::endl;

    v3 *= 2;
    std::cout << "Vector after multiplication: " << v3 << std::endl;

    std::cout << "Magnitude of vector: " << v3() << std::endl;

    std::cout << "Enter a vector (x y): ";
    std::cin >> testVec;
    std::cout << "You entered: " << testVec << std::endl;

    std::cout << "Active instances of Vector2d: " << Vector2d::getInstanceCount() << std::endl;

    return 0;
}
