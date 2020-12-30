#include "EnemyWay.hpp"

#include <stdexcept>

EnemyWay::EnemyWay()
{
    _size = 0;
    _data = nullptr;
}

EnemyWay::EnemyWay(unsigned int n)
{
    _size = n;
    _data = new glm::vec2[n];
}

EnemyWay::~EnemyWay()
{
    delete[] _data;
}

void EnemyWay::fromVector(const std::vector<glm::vec2>& vector)
{
    delete[] _data;

    _size = vector.size();
    _data = new glm::vec2[_size];
    for (unsigned int i = 0; i < _size; i++) {
        _data[i] = vector[i];
    }
}

void EnemyWay::fromVectorGrid(const std::vector<glm::vec2>& vector, float k)
{
    delete[] _data;

    _size = vector.size();
    _data = new glm::vec2[_size];
    for (unsigned int i = 0; i < _size; i++) {
        _data[i].x = vector[i].x * k + k/2;
        _data[i].y = vector[i].y * k + k/2;
    }
}

glm::vec2& EnemyWay::at(unsigned int n)
{
    if (n >= _size)
        throw std::out_of_range("out_of_range EnemyWay");
    return _data[n];
}

glm::vec2 EnemyWay::firstPoint()
{
    return at(0);
}

glm::vec2 EnemyWay::lastPoint()
{
    return at(_size - 1);
}

glm::vec2& EnemyWay::operator[](const unsigned int n)
{
    return _data[n];
}

const glm::vec2& EnemyWay::operator[](const unsigned int n) const
{
    return _data[n];
}

EnemyWay& EnemyWay::operator=(const EnemyWay& right)
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
