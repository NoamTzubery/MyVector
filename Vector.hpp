#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>

template<typename T>
class Vector
{
public:
    Vector()
    {
        Realloc(2);
    }

    ~Vector()
    {
        delete[] m_Data;
    }

    void inc_size() {
        Realloc(elements_Capacity * 2);
    }

    void push_back(const T& value)
    {
        if (elements_Size >= elements_Capacity)
        {
            inc_size();
        }
        m_Data[elements_Size++] = value;
    }

    void pop_back()
    {
        if (elements_Size > 0)
        {
            elements_Size--;
        }
        else
        {
            throw std::runtime_error("Error: Attempt to pop from an empty vector.");
        }
    }

    bool empty() const
    {
        return elements_Size == 0;
    }

    size_t size() const
    {
        return elements_Size;
    }

    size_t max_size() const
    {
        return std::numeric_limits<size_t>::max();
    }

    size_t capacity() const
    {
        return elements_Capacity;
    }

    void insert(size_t index, const T& value)
    {
        if (index > elements_Size)
        {
            throw std::out_of_range("Error: Index out of range.");
        }

        if (elements_Size >= elements_Capacity)
        {
            inc_size();
        }

        for (size_t i = elements_Size; i > index; --i)
        {
            m_Data[i] = std::move(m_Data[i - 1]);
        }

        m_Data[index] = value;
        ++elements_Size;
    }

    void reverse() {
        T temp;
        for (size_t i = 0; i < elements_Size / 2; ++i) {
            temp = m_Data[i];
            m_Data[i] = m_Data[elements_Size - i - 1];
            m_Data[elements_Size - i - 1] = temp;
        }
    }

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        if (elements_Size >= elements_Capacity)
        {
            inc_size();
        }
        new(&m_Data[elements_Size++]) T(std::forward<Args>(args)...);
    }


    const T& operator[](size_t index) const
    {
        if (index >= elements_Size)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return m_Data[index];
    }
private:
    T* m_Data = nullptr;

    size_t elements_Size = 0;
    size_t elements_Capacity = 0;

    void Realloc(size_t new_Capacity)
    {
        if (m_Data != NULL) {
            m_Data = (T*)realloc(m_Data, new_Capacity * sizeof(T));
            elements_Capacity = new_Capacity;
        }
    }
};
