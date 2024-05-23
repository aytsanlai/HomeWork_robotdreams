#include <iostream>
#include <cmath>

using namespace std;

const float PI = 3.14159265359;

float getArea(float radius) {
    return PI * radius * radius;
}

float getCircumference(float radius) {
    return 2 * PI * radius;
}

int main() {
    float radius;
    cout << "Enter the radius of the circle: ";
    cin >> radius;

    cout << "Area of the circle: " << getArea(radius) << endl;
    cout << "Circumference of the circle: " << getCircumference(radius) << endl;

    return 0;
}
