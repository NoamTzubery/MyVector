#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>

/**
 * @brief A dynamic array (vector) template class.
 *
 * @param T The type of elements stored in the vector.
 */
template<typename T>
class Vector
{
public:
    /**
     * @brief Default constructor that initializes the vector with a capacity of 2.
     */
    Vector()
    {
        Realloc(2);
    }

    /**
     * @brief Copy constructor that initializes the vector by copying another vector.
     *
     * @param other The vector to be copied.
     */
    Vector(const Vector& other)
        : elements_Size(other.elements_Size), elements_Capacity(other.elements_Capacity)
    {
        m_Data = new T[elements_Capacity];
        for (size_t i = 0; i < elements_Size; ++i)
        {
            m_Data[i] = other.m_Data[i];
        }
    }

    /**
     * @brief Destructor that cleans up the allocated memory.
     */
    ~Vector()
    {
        delete[] m_Data;
    }
    /**
     * @brief Add an element to the end of the vector.
     *
     * @param value The value to be added.
     */
    void push_back(const T& value)
    {
        if (elements_Size >= elements_Capacity)
        {
            inc_size();
        }
        m_Data[elements_Size++] = value;
    }

    /**
     * @brief Remove the last element from the vector.
     *
     * @throw std::runtime_error if the vector is empty.
     */
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

    /**
     * @brief Check if the vector is empty.
     *
     * @return true if the vector is empty, false otherwise.
     */
    bool empty() const
    {
        return elements_Size == 0;
    }

    /**
     * @brief Get the number of elements in the vector.
     *
     * @return The number of elements.
     */
    size_t size() const
    {
        return elements_Size;
    }

    /**
     * @brief Get the maximum possible number of elements in the vector.
     *
     * @return The maximum number of elements.
     */
    size_t max_size() const
    {
        return std::numeric_limits<size_t>::max();
    }

    /**
     * @brief Get the current capacity of the vector.
     *
     * @return The current capacity.
     */
    size_t capacity() const
    {
        return elements_Capacity;
    }

    /**
     * @brief Insert an element at a specified position in the vector.
     *
     * @param index The position to insert the element.
     * @param value The value to be inserted.
     * @throw std::out_of_range if the index is out of range.
     */
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

    /**
     * @brief Reverse the order of elements in the vector.
     */
    void reverse() {
        T temp;
        for (size_t i = 0; i < elements_Size / 2; ++i) {
            temp = m_Data[i];
            m_Data[i] = m_Data[elements_Size - i - 1];
            m_Data[elements_Size - i - 1] = temp;
        }
    }

    /**
     * @brief Add an element to the end of the vector by constructing it in-place.
     *
     * @param Args The types of arguments to forward to the constructor of T.
     * @param args The arguments to forward to the constructor of T.
     */
    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        if (elements_Size >= elements_Capacity)
        {
            inc_size();
        }
        new(&m_Data[elements_Size++]) T(std::forward<Args>(args)...);
    }

    /**
     * @brief Access an element at a specified position.
     *
     * @param index The position of the element.
     * @return The element at the specified position.
     * @throw std::out_of_range if the index is out of range.
     */
    const T& operator[](size_t index) const
    {
        if (index >= elements_Size)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return m_Data[index];
    }

    /**
     * @brief Access an element at a specified position with bounds checking.
     *
     * @param index The position of the element.
     * @return The element at the specified position.
     * @throw std::out_of_range if the index is out of range.
     */
    const T& at(size_t index) const
    {
        if (index >= elements_Size)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return m_Data[index];
    }

    /**
     * @brief Compare two vectors for equality.
     *
     * @param other The vector to compare with.
     * @return true if the vectors are equal, false otherwise.
     */
    bool operator==(const Vector& other) const
    {
        if (elements_Size != other.elements_Size)
        {
            return false;
        }
        for (size_t i = 0; i < elements_Size; ++i)
        {
            if (m_Data[i] != other.m_Data[i])
            {
                return false;
            }
        }
        return true;
    }

private:
    T* m_Data = nullptr;              ///< Pointer to the dynamically allocated array of elements.
    size_t elements_Size = 0;         ///< The number of elements in the vector.
    size_t elements_Capacity = 0;     ///< The capacity of the vector.

    /**
     * @brief Reallocate the vector to a new capacity.
     *
     * @param new_Capacity The new capacity.
     */
    void Realloc(size_t new_Capacity)
    {
        T* new_Data = new T[new_Capacity];
        for (size_t i = 0; i < elements_Size; ++i)
        {
            new_Data[i] = std::move(m_Data[i]);
        }
        delete[] m_Data;
        m_Data = new_Data;
        elements_Capacity = new_Capacity;
    }
    /**
     * @brief Increase the capacity of the vector by doubling it.
    */
    void inc_size() {
        Realloc(elements_Capacity * 2);
    }
};