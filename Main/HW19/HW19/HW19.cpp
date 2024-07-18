#include <iostream>
#include "DynamicIntArray.h"

int main()
{
    DynamicIntArray arr1;
    std::cout << "Default constructor: size = " << arr1.getSize() << std::endl;

    DynamicIntArray arr2(5);
    std::cout << "Constructor with size 5: size = " << arr2.getSize() << std::endl;

    arr2.push_back(10);
    std::cout << "After push_back(10): size = " << arr2.getSize() << std::endl;
    std::cout << "arr2[5] = " << arr2[5] << std::endl;

    arr2.setSize(3);
    std::cout << "After setSize(3): size = " << arr2.getSize() << std::endl;

    arr2.clear();
    std::cout << "After clear(): size = " << arr2.getSize() << std::endl;

    DynamicIntArray arr3(arr2);
    std::cout << "Copy constructor: size = " << arr3.getSize() << std::endl;

    DynamicIntArray arr4 = arr2;
    std::cout << "Assignment operator: size = " << arr4.getSize() << std::endl;

    DynamicIntArray arr5(3);
    arr5[0] = 1;
    arr5[1] = 2;
    arr5[2] = 3;

    DynamicIntArray arr6(3);
    arr6[0] = 1;
    arr6[1] = 2;
    arr6[2] = 3;

    std::cout << "arr5 == arr6: " << (arr5 == arr6) << std::endl;
    std::cout << "arr5 != arr6: " << (arr5 != arr6) << std::endl;

    return 0;
}
