#include "ModelGL.hpp"

#include <utility>

#include <iostream>

MaterialGL::MaterialGL()
{
	std::cout << "MaterialGL()\n";
}

MaterialGL::MaterialGL(MaterialGL&& materialGL) :
	textures_id(std::move(materialGL.textures_id))
{
	std::cout << "MaterialGL(MaterialGL&& materialGL)\n";
}

MaterialGL::~MaterialGL()
{
	std::cout << "~MaterialGL()\n";
	this->textures_id.clear();
}

MaterialGL& MaterialGL::operator=(MaterialGL&& materialGL)
{
	std::cout << "MaterialGL& operator=(MaterialGL&& materialGL)\n";
	if (&materialGL == this)
		return *this;

	this->textures_id.clear();
	this->textures_id = std::move(materialGL.textures_id);

	return *this;
}


MeshGL::MeshGL()
{
	std::cout << "MeshGL()\n";
}

MeshGL::MeshGL(MeshGL&& meshGL) :
	materialGL(std::move(meshGL.materialGL))
{
	std::cout << "MeshGL(MeshGL&& mesh)\n";
	this->VAO = meshGL.VAO;
	this->VBO = meshGL.VBO;
	this->EBO = meshGL.EBO;
	this->size = meshGL.size;
}

MeshGL::~MeshGL()
{
	std::cout << "~MeshGL()\n";
}

MeshGL& MeshGL::operator=(MeshGL&& meshGL)
{
	std::cout << "MeshGL& operator=(Mesh&& mesh)\n";
	if (&meshGL == this)
		return *this;

	this->VAO = meshGL.VAO;
	this->VBO = meshGL.VBO;
	this->EBO = meshGL.EBO;
	this->size = meshGL.size;
	this->materialGL = std::move(meshGL.materialGL);

	return *this;
}


ModelGL::ModelGL()
{
	std::cout << "ModelGL()\n";
}

ModelGL::ModelGL(ModelGL&& modelGL) :
	meshesGL(std::move(modelGL.meshesGL))
{
	std::cout << "ModelGL(ModelGL&& modelGL)\n";
}

ModelGL::~ModelGL()
{
	std::cout << "~ModelGL()\n";
}

ModelGL& ModelGL::operator=(ModelGL&& modelGL)
{
	std::cout << "ModelGL& operator=(ModelGL&& modelGL)\n";
	if (&modelGL == this)
		return *this;

	this->meshesGL = std::move(modelGL.meshesGL);
	return *this;
}



std::map<std::string, ModelGL> modelsGL_map;

GLuint load_texture_OGL(Image* image)
{
	GLuint textureID;
	gl::GenTextures(1, &textureID);

	GLenum format;
	if (image->channels == 1)
		format = gl::RED;
	else if (image->channels == 3)
		format = gl::RGB;
	else if (image->channels == 4)
		format = gl::RGBA;

	gl::BindTexture(gl::TEXTURE_2D, textureID);
	gl::TexImage2D(gl::TEXTURE_2D, 0, format, image->width, image->height, 0, format, gl::UNSIGNED_BYTE, image->data);
	gl::GenerateMipmap(gl::TEXTURE_2D);

	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);

	return textureID;
}

MeshGL load_mesh_OGL(const Mesh& mesh)
{
	MeshGL meshGL;

	meshGL.size = mesh.indices.size();

	gl::GenVertexArrays(1, &meshGL.VAO);
	gl::GenBuffers(1, &meshGL.VBO);
	gl::GenBuffers(1, &meshGL.EBO);

	gl::BindVertexArray(meshGL.VAO);
	gl::BindBuffer(gl::ARRAY_BUFFER, meshGL.VBO);

	gl::BufferData(gl::ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], gl::STATIC_DRAW);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, meshGL.EBO);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], gl::STATIC_DRAW);

	// vertex positions
	gl::EnableVertexAttribArray(0);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, sizeof(Vertex), (void*)0);

	// vertex texture coords
	gl::EnableVertexAttribArray(1);
	gl::VertexAttribPointer(1, 2, gl::FLOAT, gl::FALSE_, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	gl::BindVertexArray(0);

	Image* img = mesh.material.textures.at(TextureType::DIFFUSE).get();
	meshGL.materialGL.textures_id[TextureType::DIFFUSE] = load_texture_OGL(img);

	return meshGL;
}

ModelGL* load_model_OGL(std::string name)
{
	auto search = modelsGL_map.find(name);
	if (search != modelsGL_map.end())
		return &search->second;

	Model* model = get_model(name);
	if (model == nullptr)
		//throw std::runtime_error();
		return nullptr;

	modelsGL_map[name];

	for (const auto& mesh : model->meshes)
	{
		modelsGL_map[name].meshesGL.push_back(load_mesh_OGL(mesh));
	}

	return &modelsGL_map[name];
}

void unload_model_OGL(std::string name)
{
	// TODO
}
