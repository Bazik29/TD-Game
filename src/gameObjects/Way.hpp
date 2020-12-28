#pragma once

#include <glm/vec2.hpp>
#include <vector>

class Way {
public:
    Way();
    Way(unsigned int n);
    ~Way();

    Way(const Way&) = delete;

    void fromVector(const std::vector<glm::vec2>& vector);
    inline unsigned int size();
    glm::vec2& at(unsigned int n);

    glm::vec2& operator[](const unsigned int n);
    const glm::vec2& operator[](const unsigned int n) const;

    Way& operator=(const Way& right);

private:
    glm::vec2* _data;
    unsigned int _size;
};

inline unsigned int Way::size()
{
    return _size;
}
