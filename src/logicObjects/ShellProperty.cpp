#include "ShellProperty.hpp"

ShellProperty::ShellProperty()
{
    this->speed = 0.0f;
    this->color = glm::vec4(1.0f);
}

ShellProperty::ShellProperty(float speed, const glm::vec4& color)
{
    init(speed, color);
}

void ShellProperty::init(float speed, const glm::vec4& color)
{
    this->speed = speed;
    this->color = color;
}

ShellProperty::~ShellProperty()
{
}
