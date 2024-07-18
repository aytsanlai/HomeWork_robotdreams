#pragma once
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

template <typename T>
class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(std::size_t size);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other);

    T& operator[](std::size_t index);

    void setSize(std::size_t newSize);
    std::size_t getSize() const;

    void clear();

    void push_back(const T& element);

    void pop_back();
    T back() const;

    void reserve(std::size_t reservedSpace);
    std::size_t getCapacity() const;

    void shrinkToFit();

    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

private:
    std::size_t m_size;
    std::size_t m_capacity;
    T* m_array;
};

#include "DynamicArray.tpp"
