#include <iostream>
#include "Vector2d.h"
#include "Vector3d.h"

int main() {
    
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

    std::cout << "Dot Product: " << v1.dotProduct(v2) << std::endl;

    Vector2d v5 = v1.negate();
    std::cout << "Negated vector: " << v5 << std::endl;

    Vector2d v6{ 0, 0, 1, 1 }; 
    std::cout << "Vector from points (0,0) to (1,1): " << v6 << std::endl;

    auto relativeState = v1.getRelativeState(v2);
    std::cout << "Relative state of v1 and v2: ";
    switch (relativeState) {
    case VectorRelativeState::Identical: std::cout << "Identical"; break;
    case VectorRelativeState::coDirected: std::cout << "coDirected"; break;
    case VectorRelativeState::OppositeDirected: std::cout << "OppositeDirected"; break;
    case VectorRelativeState::AcuteAngle: std::cout << "AcuteAngle"; break;
    case VectorRelativeState::ObtuseAngle: std::cout << "ObtuseAngle"; break;
    case VectorRelativeState::RightAngle: std::cout << "RightAngle"; break;
    }
    std::cout << std::endl;

    v6.scale(2.0, 3.0);
    std::cout << "Scaled vector: " << v6 << std::endl;

    std::cout << "Active instances of Vector2d: " << Vector2d::getInstanceCount() << std::endl;

    Vector3d v7{ 1.0, 2.0, 3.0 };
    Vector3d v8{ 4.0, 5.0, 6.0 };

    Vector3d v9 = v7 + v8;
    std::cout << "Vector3d Addition: " << v9 << std::endl;

    Vector3d v10 = v7.crossProduct(v8);
    std::cout << "Vector3d Cross Product: " << v10 << std::endl;

    std::cout << "Magnitude of Vector3d: " << v9() << std::endl;

    return 0;
}
