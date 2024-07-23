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
    static const size_t InitialCapacity = 2; ///< Initial capacity of the vector

    Vector();
    Vector(const Vector& other);
    ~Vector();

    /**
     * @brief Add an element to the end of the vector.
     *
     * @param value The value to be added.
     */
    void PushBack(const T& value);

    /**
     * @brief Remove the last element from the vector.
     *
     * @throw std::runtime_error if the vector is empty.
     */
    void PopBack();

    /**
     * @brief Check if the vector is empty.
     *
     * @return true if the vector is empty, false otherwise.
     */
    bool IsEmpty() const;

    /**
     * @brief Get the number of elements in the vector.
     *
     * @return The number of elements.
     */
    size_t Size() const;

    /**
     * @brief Get the maximum possible number of elements in the vector.
     *
     * @return The maximum number of elements.
     */
    size_t MaxSize() const;

    /**
     * @brief Get the current capacity of the vector.
     *
     * @return The current capacity.
     */
    size_t Capacity() const;

    /**
     * @brief Insert an element at a specified position in the vector.
     *
     * @param index The position to insert the element.
     * @param value The value to be inserted.
     * @throw std::out_of_range if the index is out of range.
     */
    void Insert(size_t index, const T& value);

    /**
     * @brief Reverse the order of elements in the vector.
     */
    void Reverse();

    /**
     * @brief Add an element to the end of the vector by constructing it in-place.
     *
     * @param Args The types of arguments to forward to the constructor of T.
     * @param args The arguments to forward to the constructor of T.
     */
    template<typename... Args>
    void EmplaceBack(Args&&... args);

    /**
     * @brief Access an element at a specified position.
     *
     * @param index The position of the element.
     * @return The element at the specified position.
     * @throw std::out_of_range if the index is out of range.
     */
    const T& operator[](size_t index) const;

    /**
     * @brief Access an element at a specified position with bounds checking.
     *
     * @param index The position of the element.
     * @return The element at the specified position.
     * @throw std::out_of_range if the index is out of range.
     */
    const T& At(size_t index) const;

    /**
     * @brief Compare two vectors for equality.
     *
     * @param other The vector to compare with.
     * @return true if the vectors are equal, false otherwise.
     */
    bool operator==(const Vector& other) const;

private:
    T* _data;             ///< Pointer to the dynamically allocated array of elements.
    size_t _size;         ///< The number of elements in the vector.
    size_t _capacity;     ///< The capacity of the vector.

    /**
     * @brief Reallocate the vector to a new capacity.
     *
     * @param newCapacity The new capacity.
     */
    void Realloc(size_t newCapacity);

    /**
     * @brief Increase the capacity of the vector by doubling it.
    */
    void IncreaseSize();
};

#include "Vector.cpp"
