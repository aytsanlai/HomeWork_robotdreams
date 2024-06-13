#include "rectangle.h"

Rectangle::Rectangle() : length(0), height(0) {}

Rectangle::Rectangle(float l, float h) : length(l), height(h) {}

float Rectangle::getArea() const {
    return length * height;
}

float Rectangle::getPerimeter() const {
    return 2 * (length + height);
}
