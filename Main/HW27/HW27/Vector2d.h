#pragma once

#include <iostream>
#include <cmath>

enum class VectorRelativeState {
    Identical,
    coDirected,
    OppositeDirected,
    AcuteAngle,
    ObtuseAngle,
    RightAngle
};

class Vector2d {
public:
    float x, y;
    static int count;

    Vector2d(float x = 0.0, float y = 0.0);
    Vector2d(float x0, float y0, float x1, float y1); 
    Vector2d(const Vector2d& other);
    ~Vector2d();

    Vector2d& operator=(const Vector2d& other);
    void operator*=(float scalar);
    float operator()() const;
    float& operator[](std::size_t idx);

    float dotProduct(const Vector2d& other) const;
    Vector2d negate() const;
    VectorRelativeState getRelativeState(const Vector2d& other) const;
    void scale(float factorX, float factorY);

    friend Vector2d operator+(const Vector2d& v1, const Vector2d& v2);
    friend Vector2d operator-(const Vector2d& v1, const Vector2d& v2);
    friend std::ostream& operator<<(std::ostream& os, const Vector2d& v);
    friend std::istream& operator>>(std::istream& is, Vector2d& v);

    static int getInstanceCount();
};
