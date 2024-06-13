#pragma once

class Rectangle {
private:
    float length;
    float height;

public:
    Rectangle();
    Rectangle(float l, float h);
    float getArea() const;
    float getPerimeter() const;
};
