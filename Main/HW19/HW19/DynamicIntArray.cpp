#include "DynamicIntArray.h"

DynamicIntArray::DynamicIntArray()
    : m_size(0), m_array(nullptr) {}

DynamicIntArray::DynamicIntArray(std::size_t size)
    : m_size(size), m_array(new int[size]()) {}

DynamicIntArray::DynamicIntArray(const DynamicIntArray& other)
    : m_size(other.m_size), m_array(new int[other.m_size])
{
    std::copy(other.m_array, other.m_array + other.m_size, m_array);
}

DynamicIntArray::~DynamicIntArray()
{
    delete[] m_array;
}

DynamicIntArray& DynamicIntArray::operator=(const DynamicIntArray& other)
{
    if (this != &other)
    {
        delete[] m_array;
        m_size = other.m_size;
        m_array = new int[m_size];
        std::copy(other.m_array, other.m_array + m_size, m_array);
    }
    return *this;
}

int& DynamicIntArray::operator[](std::size_t index)
{
    if (index >= m_size)
    {
        throw std::out_of_range("Index out of range");
    }
    return m_array[index];
}

void DynamicIntArray::setSize(std::size_t newSize)
{
    int* newArray = new int[newSize]();
    std::size_t copySize = (newSize < m_size) ? newSize : m_size;
    std::copy(m_array, m_array + copySize, newArray);
    delete[] m_array;
    m_array = newArray;
    m_size = newSize;
}

std::size_t DynamicIntArray::getSize() const
{
    return m_size;
}

void DynamicIntArray::clear()
{
    delete[] m_array;
    m_array = nullptr;
    m_size = 0;
}

bool DynamicIntArray::operator==(const DynamicIntArray& other) const
{
    if (m_size != other.m_size)
    {
        return false;
    }
    for (std::size_t i = 0; i < m_size; ++i)
    {
        if (m_array[i] != other.m_array[i])
        {
            return false;
        }
    }
    return true;
}

bool DynamicIntArray::operator!=(const DynamicIntArray& other) const
{
    return !(*this == other);
}

void DynamicIntArray::push_back(int element)
{
    int* newArray = new int[m_size + 1];
    std::copy(m_array, m_array + m_size, newArray);
    newArray[m_size] = element;
    delete[] m_array;
    m_array = newArray;
    ++m_size;
}
