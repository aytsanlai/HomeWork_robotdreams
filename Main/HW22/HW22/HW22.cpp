#include <iostream>
#include "DynamicArray.h"

int main()
{
    DynamicArray<int> m_container;
    m_container.reserve(4);
    m_container.push_back(25);
    m_container.push_back(30);
    m_container.push_back(10);
    m_container.push_back(39);

    std::cout << "Container size: " << m_container.getSize() << std::endl;
    std::cout << "Container capacity: " << m_container.getCapacity() << std::endl;

    m_container.push_back(55);
    std::cout << "After adding the 5th element:" << std::endl;
    std::cout << "Container size: " << m_container.getSize() << std::endl;
    std::cout << "Container capacity: " << m_container.getCapacity() << std::endl;

    m_container.pop_back();
    std::cout << "After popping the last element:" << std::endl;
    std::cout << "Container size: " << m_container.getSize() << std::endl;
    std::cout << "Last element: " << m_container.back() << std::endl;

    return 0;
}
