#pragma once

#include <glm/vec2.hpp>
#include <vector>

class EnemyWay {
public:
    EnemyWay();
    EnemyWay(unsigned int n);
    ~EnemyWay();

    EnemyWay(const EnemyWay&) = delete;

    void fromVector(const std::vector<glm::vec2>& vector);
    void fromVectorGrid(const std::vector<glm::uvec2>& vector, float scale);
    inline unsigned int size();
    glm::vec2& at(unsigned int n);

    glm::vec2 firstPoint();
    glm::vec2 lastPoint();

    glm::vec2& operator[](const unsigned int n);
    const glm::vec2& operator[](const unsigned int n) const;

    EnemyWay& operator=(const EnemyWay& right);

private:
    glm::vec2* _data;
    unsigned int _size;
};

inline unsigned int EnemyWay::size()
{
    return _size;
}
