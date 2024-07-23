#include "Vector.hpp"

template<typename T>
const size_t Vector<T>::InitialCapacity;

template<typename T>
Vector<T>::Vector()
    : _data(nullptr), _size(0), _capacity(0)
{
    Realloc(InitialCapacity);
}

template<typename T>
Vector<T>::Vector(const Vector& other)
    : _size(other._size), _capacity(other._capacity)
{
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i)
    {
        _data[i] = other._data[i];
    }
}

template<typename T>
Vector<T>::~Vector()
{
    delete[] _data;
}

template<typename T>
void Vector<T>::PushBack(const T& value)
{
    if (_size >= _capacity)
    {
        IncreaseSize();
    }
    _data[_size++] = value;
}

template<typename T>
void Vector<T>::PopBack()
{
    if (_size > 0)
    {
        _size--;
    }
    else
    {
        throw std::runtime_error("Error: Attempt to pop from an empty vector.");
    }
}

template<typename T>
bool Vector<T>::IsEmpty() const
{
    return _size == 0;
}

template<typename T>
size_t Vector<T>::Size() const
{
    return _size;
}

template<typename T>
size_t Vector<T>::MaxSize() const
{
    return std::numeric_limits<size_t>::max();
}

template<typename T>
size_t Vector<T>::Capacity() const
{
    return _capacity;
}

template<typename T>
void Vector<T>::Insert(size_t index, const T& value)
{
    if (index > _size)
    {
        throw std::out_of_range("Error: Index out of range.");
    }

    if (_size >= _capacity)
    {
        IncreaseSize();
    }

    for (size_t i = _size; i > index; --i)
    {
        _data[i] = std::move(_data[i - 1]);
    }

    _data[index] = value;
    ++_size;
}

template<typename T>
void Vector<T>::Reverse()
{
    T temp;
    for (size_t i = 0; i < _size / 2; ++i)
    {
        temp = _data[i];
        _data[i] = _data[_size - i - 1];
        _data[_size - i - 1] = temp;
    }
}

template<typename T>
template<typename... Args>
void Vector<T>::EmplaceBack(Args&&... args)
{
    if (_size >= _capacity)
    {
        IncreaseSize();
    }
    new(&_data[_size++]) T(std::forward<Args>(args)...);
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
    if (index >= _size)
    {
        throw std::out_of_range("Error: Index out of range.");
    }
    return _data[index];
}

template<typename T>
const T& Vector<T>::At(size_t index) const
{
    if (index >= _size)
    {
        throw std::out_of_range("Error: Index out of range.");
    }
    return _data[index];
}

template<typename T>
bool Vector<T>::operator==(const Vector& other) const
{
    if (_size != other._size)
    {
        return false;
    }
    for (size_t i = 0; i < _size; ++i)
    {
        if (_data[i] != other._data[i])
        {
            return false;
        }
    }
    return true;
}

template<typename T>
void Vector<T>::Realloc(size_t newCapacity)
{
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < _size; ++i)
    {
        newData[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data = newData;
    _capacity = newCapacity;
}

template<typename T>
void Vector<T>::IncreaseSize()
{
    Realloc(_capacity == 0 ? InitialCapacity : _capacity * 2);
}



