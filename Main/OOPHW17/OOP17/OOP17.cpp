#include <iostream>
#include <cmath>

class Vector2d {
public:
    float x, y;
    static int count;

    Vector2d(float x = 0.0, float y = 0.0) : x(x), y(y) {
        count++;
    }

    Vector2d(const Vector2d& other) : x(other.x), y(other.y) {
        count++;
    }

    ~Vector2d() {
        count--;
    }

    Vector2d& operator=(const Vector2d& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    void operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
    }

    float operator()() const {
        return std::sqrt(x * x + y * y);
    }

    float& operator[](std::size_t idx) {
        if (idx == 0) return x;
        else if (idx == 1) return y;
        else throw std::out_of_range("Index out of range");
    }

    friend Vector2d operator+(const Vector2d& v1, const Vector2d& v2);
    friend Vector2d operator-(const Vector2d& v1, const Vector2d& v2);
    friend std::ostream& operator<<(std::ostream& os, const Vector2d& v);
    friend std::istream& operator>>(std::istream& is, Vector2d& v);

    static int getInstanceCount() {
        return count;
    }
};

int Vector2d::count = 0;

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
