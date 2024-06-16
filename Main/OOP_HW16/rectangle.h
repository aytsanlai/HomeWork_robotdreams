#pragma once

class Rectangle {
private:
    float length;
    float height;

public:
    Rectangle();
    Rectangle(float l, float h);
    [[nodiscard]] float getArea() const;
    [[nodiscard]] float getPerimeter() const;
};
