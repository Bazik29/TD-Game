#pragma once

#include <nlohmann/json.hpp>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace glm {

void to_json(nlohmann::json& j, const glm::vec2& vec)
{
    j = nlohmann::json {
        { "x", vec.x },
        { "y", vec.y }
    };
}

void from_json(const nlohmann::json& j, glm::vec2& vec)
{
    j.at("x").get_to(vec.x);
    j.at("y").get_to(vec.y);
}

void to_json(nlohmann::json& j, const glm::vec3& vec)
{
    j = nlohmann::json {
        { "x", vec.x },
        { "y", vec.y },
        { "z", vec.z }
    };
}

void from_json(const nlohmann::json& j, glm::vec3& vec)
{
    j.at("x").get_to(vec.x);
    j.at("y").get_to(vec.y);
    j.at("z").get_to(vec.z);
}

void from_json(const nlohmann::json& j, glm::vec4& vec)
{
    j.at("x").get_to(vec.x);
    j.at("y").get_to(vec.y);
    j.at("z").get_to(vec.z);
    j.at("w").get_to(vec.w);
}

void to_json(nlohmann::json& j, const glm::vec4& vec)
{
    j = nlohmann::json {
        { "x", vec.x },
        { "y", vec.y },
        { "z", vec.z },
        { "w", vec.w }
    };
};

} // namespace glm

void to_json(nlohmann::json& j, const LevelDiscription& l_d)
{
    j = nlohmann::json {
        { "serial_number", l_d.serial_number },
        { "path", l_d.path }
    };
}

void from_json(const nlohmann::json& j, LevelDiscription& l_d)
{
    j.at("serial_number").get_to(l_d.serial_number);
    j.at("path").get_to(l_d.path);
}
