#include "Way.hpp"

#include <stdexcept>

Way::Way()
{
    _size = 0;
    _data = nullptr;
}

Way::Way(unsigned int n)
{
    _size = n;
    _data = new glm::vec2[n];
}

Way::~Way()
{
    delete[] _data;
}

void Way::fromVector(const std::vector<glm::vec2>& vector)
{
    delete[] _data;

    _size = vector.size();
    _data = new glm::vec2[_size];
    for (unsigned int i = 0; i < _size; i++) {
        _data[i] = vector[i];
    }
}

glm::vec2& Way::at(unsigned int n)
{
    if (n >= _size)
        throw std::out_of_range("Way");
    return _data[n];
}

glm::vec2& Way::operator[](const unsigned int n)
{
    return _data[n];
}

const glm::vec2& Way::operator[](const unsigned int n) const
{
    return _data[n];
}

Way& Way::operator=(const Way& right)
{
    if (this == &right) {
        return *this;
    }

    delete[] _data;

    _size = right._size;
    _data = new glm::vec2[_size];
    for (unsigned int i = 0; i < _size; i++) {
        _data[i] = right._data[i];
    }
    return *this;
}
