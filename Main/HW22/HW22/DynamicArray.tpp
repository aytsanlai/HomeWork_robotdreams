#include "DynamicArray.h"

template<typename T>
DynamicArray<T>::DynamicArray()
    : m_size(0), m_capacity(0), m_array(nullptr) {}

template<typename T>
DynamicArray<T>::DynamicArray(std::size_t size)
    : m_size(size), m_capacity(size), m_array(new T[size]()) {}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
    : m_size(other.m_size), m_capacity(other.m_capacity), m_array(new T[other.m_capacity])
{
    std::copy(other.m_array, other.m_array + other.m_size, m_array);
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] m_array;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
    if (this != &other)
    {
        delete[] m_array;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_array = new T[m_capacity];
        std::copy(other.m_array, other.m_array + m_size, m_array);
    }
    return *this;
}

template<typename T>
T& DynamicArray<T>::operator[](std::size_t index)
{
    if (index >= m_size)
    {
        throw std::out_of_range("Index out of range");
    }
    return m_array[index];
}

template<typename T>
void DynamicArray<T>::setSize(std::size_t newSize)
{
    if (newSize > m_capacity)
    {
        reserve(newSize);
    }
    m_size = newSize;
}

template<typename T>
std::size_t DynamicArray<T>::getSize() const
{
    return m_size;
}

template<typename T>
void DynamicArray<T>::clear()
{
    delete[] m_array;
    m_array = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template<typename T>
bool DynamicArray<T>::operator==(const DynamicArray& other) const
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

template<typename T>
bool DynamicArray<T>::operator!=(const DynamicArray& other) const
{
    return !(*this == other);
}

template<typename T>
void DynamicArray<T>::push_back(const T& element)
{
    if (m_size >= m_capacity)
    {
        reserve(m_capacity > 0 ? m_capacity * 2 : 1);
    }
    m_array[m_size++] = element;
}

template<typename T>
void DynamicArray<T>::reserve(std::size_t reservedSpace)
{
    if (reservedSpace > m_capacity)
    {
        T* newArray = new T[reservedSpace];
        std::copy(m_array, m_array + m_size, newArray);
        delete[] m_array;
        m_array = newArray;
        m_capacity = reservedSpace;
    }
}

template<typename T>
std::size_t DynamicArray<T>::getCapacity() const
{
    return m_capacity;
}

template<typename T>
void DynamicArray<T>::shrinkToFit()
{
    if (m_capacity > m_size)
    {
        T* newArray = new T[m_size];
        std::copy(m_array, m_array + m_size, newArray);
        delete[] m_array;
        m_array = newArray;
        m_capacity = m_size;
    }
}

template<typename T>
void DynamicArray<T>::pop_back()
{
    if (m_size > 0)
    {
        --m_size;
    }
    else
    {
        throw std::out_of_range("Array is empty");
    }
}

template<typename T>
T DynamicArray<T>::back() const
{
    if (m_size > 0)
    {
        return m_array[m_size - 1];
    }
    else
    {
        throw std::out_of_range("Array is empty");
    }
}
