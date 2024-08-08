#include "Vector2d.h"

int Vector2d::count = 0;

Vector2d::Vector2d(float x, float y) : x(x), y(y) {
    count++;
}

Vector2d::Vector2d(float x0, float y0, float x1, float y1)
    : x(x1 - x0), y(y1 - y0) {
    count++;
}

Vector2d::Vector2d(const Vector2d& other) : x(other.x), y(other.y) {
    count++;
}

Vector2d::~Vector2d() {
    count--;
}

Vector2d& Vector2d::operator=(const Vector2d& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

void Vector2d::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
}

float Vector2d::operator()() const {
    return std::sqrt(x * x + y * y);
}

float& Vector2d::operator[](std::size_t idx) {
    if (idx == 0) return x;
    else if (idx == 1) return y;
    else throw std::out_of_range("Index out of range");
}

float Vector2d::dotProduct(const Vector2d& other) const {
    return x * other.x + y * other.y;
}

Vector2d Vector2d::negate() const {
    return Vector2d(-x, -y);
}

VectorRelativeState Vector2d::getRelativeState(const Vector2d& other) const {
    float dot = dotProduct(other);
    float cross = x * other.y - y * other.x;

    if (dot == 0 && cross == 0)
        return VectorRelativeState::Identical;
    if (dot > 0 && cross == 0)
        return VectorRelativeState::coDirected;
    if (dot < 0 && cross == 0)
        return VectorRelativeState::OppositeDirected;
    if (dot > 0 && cross != 0)
        return VectorRelativeState::AcuteAngle;
    if (dot < 0)
        return VectorRelativeState::ObtuseAngle;
    if (dot == 0 && cross != 0)
        return VectorRelativeState::RightAngle;

    return VectorRelativeState::AcuteAngle;
}

void Vector2d::scale(float factorX, float factorY) {
    x *= factorX;
    y *= factorY;
}

Vector2d operator+(const Vector2d& v1, const Vector2d& v2) {
    return Vector2d(v1.x + v2.x, v1.y + v2.y);
}

Vector2d operator-(const Vector2d& v1, const Vector2d& v2) {
    return Vector2d(v1.x - v2.x, v1.y - v2.y);
}

std::ostream& operator<<(std::ostream& os, const Vector2d& v) {
    return os << "{" << v.x << "; " << v.y << "}";
}

std::istream& operator>>(std::istream& is, Vector2d& v) {
    is >> v.x >> v.y;
    return is;
}

int Vector2d::getInstanceCount() {
    return count;
}
