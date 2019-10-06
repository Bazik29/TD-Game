#include "gl_core_4_3.hpp"

#include "FS.hpp"

#include <map>
#include <vector>
#include <string>

#include "Model.hpp"

struct MaterialGL
{
	std::map<TextureType, GLuint> textures_id;

	MaterialGL();
	MaterialGL(const MaterialGL& materialGL) = delete;
	MaterialGL(MaterialGL&& materialGL);
	~MaterialGL();

	MaterialGL& operator=(const MaterialGL& materialGL) = delete;
	MaterialGL& operator=(MaterialGL&& materialGL);
};

struct MeshGL
{
	GLuint VAO, VBO, EBO;
	unsigned int size;
	MaterialGL materialGL;

	MeshGL();
	MeshGL(const MeshGL& mesh) = delete;
	MeshGL(MeshGL&& meshGL);
	~MeshGL();

	MeshGL& operator=(const MeshGL& mesh) = delete;
	MeshGL& operator=(MeshGL&& meshGL);
};

struct ModelGL
{
	std::vector<MeshGL> meshesGL;

	ModelGL();
	ModelGL(const ModelGL& modelGL) = delete;
	ModelGL(ModelGL&& modelGL);
	~ModelGL();

	ModelGL& operator=(const ModelGL& modelGL) = delete;
	ModelGL& operator=(ModelGL&& modelGL);
};


ModelGL* load_model_OGL(std::string name);
void unload_model_OGL(std::string name);
