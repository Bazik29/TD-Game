#pragma once

#include <glm/vec4.hpp>

class ShellProperty {
public:
    ShellProperty();
    ShellProperty(float speed, const glm::vec4& color);
    ~ShellProperty();
    ShellProperty(const ShellProperty& other) = default;
    ShellProperty(ShellProperty&& other) = default;
    ShellProperty& operator=(const ShellProperty& other) = default;
    ShellProperty& operator=(ShellProperty&& other) = default;

    void init(float speed, const glm::vec4& color);

    inline float getSpeed() const;
    inline void setSpeed(float speed);
    inline glm::vec4 getColor() const;
    inline void setColor(const glm::vec4& color);

private:
    float speed;
    glm::vec4 color;
};

inline float ShellProperty::getSpeed() const
{
    return speed;
}

inline void ShellProperty::setSpeed(float speed)
{
    this->speed = speed;
}

inline glm::vec4 ShellProperty::getColor() const
{
    return color;
}

inline void ShellProperty::setColor(const glm::vec4& color)
{
    this->color = color;
}
