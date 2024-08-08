#pragma once

#include <iostream>
#include <cmath>

class Vector3d {
public:
    float x, y, z;

    Vector3d(float x = 0.0, float y = 0.0, float z = 0.0);
    Vector3d(const Vector3d& other);
    ~Vector3d();

    Vector3d& operator=(const Vector3d& other);
    void operator*=(float scalar);
    float operator()() const;
    float& operator[](std::size_t idx);

    Vector3d crossProduct(const Vector3d& other) const;

    friend Vector3d operator+(const Vector3d& v1, const Vector3d& v2);
    friend Vector3d operator-(const Vector3d& v1, const Vector3d& v2);
    friend std::ostream& operator<<(std::ostream& os, const Vector3d& v);
    friend std::istream& operator>>(std::istream& is, Vector3d& v);
};
