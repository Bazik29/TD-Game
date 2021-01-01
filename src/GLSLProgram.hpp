#pragma once

#include <FileSystem.hpp>
#include <gl_core_4_3.hpp>
#include <map>
#include <string>
#include <vector>

#include <glm/glm.hpp>

class GLSLProgramException : public std::runtime_error {
public:
    GLSLProgramException(const std::string& msg)
        : std::runtime_error(msg) {};
};

namespace GLS {

enum class ShaderType : unsigned {
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    TESS_CONTROL,
    TESS_EVALUATION,
    COMPUTE
};

const std::map<std::string, ShaderType> ShaderFileExtension = {
    { ".vert", GLS::ShaderType::VERTEX },
    { ".frag", GLS::ShaderType::FRAGMENT },
    { ".geom", GLS::ShaderType::GEOMETRY },
    { ".comp", GLS::ShaderType::COMPUTE },
    { ".tessc", GLS::ShaderType::TESS_CONTROL },
    { ".tesse", GLS::ShaderType::TESS_EVALUATION }
};

const std::map<ShaderType, unsigned int> ShaderTypeHash = {
    { ShaderType::VERTEX, gl::VERTEX_SHADER },
    { ShaderType::FRAGMENT, gl::FRAGMENT_SHADER },
    { ShaderType::GEOMETRY, gl::GEOMETRY_SHADER },
    { ShaderType::TESS_CONTROL, gl::TESS_CONTROL_SHADER },
    { ShaderType::TESS_EVALUATION, gl::TESS_EVALUATION_SHADER },
    { ShaderType::COMPUTE, gl::COMPUTE_SHADER }
};

} // namespace GLS

class GLSLProgram {
    GLuint handle;
    GLboolean linked;
    std::map<std::string, GLint> uniforms;

public:
    GLSLProgram();
    ~GLSLProgram();
    GLint getHandle();
    void start();
    void stop();
    void attach(fs::path pathToFile);
    void attach(const char* source, GLS::ShaderType type, const char* descriptor = 0);
    void link();
    GLboolean isLinked();

    void addUniformLocation(std::string name);
    void setUniform(std::string name, int value);
    void setUniform(std::string name, float value);
    void setUniform(std::string name, bool value);
    void setUniform(std::string name, float x, float y);
    void setUniform(std::string name, float x, float y, float z);
    void setUniform(std::string name, float x, float y, float z, float w);

    void setUniform(std::string name, glm::mat4 mat4);

    void setUniform(std::string name, glm::vec3 v);
    void setUniform(std::string name, glm::vec4 v);

    void setUniform(std::string name, std::vector<glm::vec4> arr);

    void setUniform4fv(std::string name, std::vector<float> arr);
};
