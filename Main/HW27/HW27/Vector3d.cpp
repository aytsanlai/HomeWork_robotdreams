#include "Vector3d.h"

Vector3d::Vector3d(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3d::Vector3d(const Vector3d& other) : x(other.x), y(other.y), z(other.z) {}

Vector3d::~Vector3d() {}

Vector3d& Vector3d::operator=(const Vector3d& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

void Vector3d::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

float Vector3d::operator()() const {
    return std::sqrt(x * x + y * y + z * z);
}

float& Vector3d::operator[](std::size_t idx) {
    if (idx == 0) return x;
    else if (idx == 1) return y;
    else if (idx == 2) return z;
    else throw std::out_of_range("Index out of range");
}

Vector3d Vector3d::crossProduct(const Vector3d& other) const {
    return Vector3d(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

Vector3d operator+(const Vector3d& v1, const Vector3d& v2) {
    return Vector3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3d operator-(const Vector3d& v1, const Vector3d& v2) {
    return Vector3d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

std::ostream& operator<<(std::ostream& os, const Vector3d& v) {
    return os << "{" << v.x << "; " << v.y << "; " << v.z << "}";
}

std::istream& operator>>(std::istream& is, Vector3d& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}
