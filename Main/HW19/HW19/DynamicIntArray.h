#pragma once
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

class DynamicIntArray
{
public:
 
    DynamicIntArray();

    DynamicIntArray(std::size_t size);

    DynamicIntArray(const DynamicIntArray& other);

    ~DynamicIntArray();

    DynamicIntArray& operator=(const DynamicIntArray& other);

    int& operator[](std::size_t index);

    void setSize(std::size_t newSize);
    std::size_t getSize() const;

    void clear();

    bool operator==(const DynamicIntArray& other) const;
    bool operator!=(const DynamicIntArray& other) const;

    void push_back(int element);

private:
    std::size_t m_size;
    int* m_array;
};
