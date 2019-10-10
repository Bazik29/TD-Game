#pragma once

#include "gl_core_4_3.hpp"

#include "FS.hpp"

#include <map>
#include <vector>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

enum class TextureType
{
	DIFFUSE
};

struct Image
{
	fs::path path;

	unsigned char* data;
	int width;
	int height;
	int channels;

	Image();
	Image(fs::path path, unsigned char* data, unsigned int width, unsigned int height, unsigned int channels);
	Image(const Image& image) = delete;
	Image(Image&& image);
	~Image();

	Image& operator=(const Image& image) = delete;
	Image& operator=(Image&& image);
};

struct Material
{
	std::map<TextureType, std::shared_ptr<Image>> textures;

	Material();
	Material(const Material& material) = delete;
	Material(Material&& material);
	~Material();

	Material& operator=(const Material& material) = delete;
	Material& operator=(Material&& material);
};

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoords;
};

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Material material;

	Mesh();
	Mesh(const Mesh& mesh) = delete;
	Mesh(Mesh&& mesh);
	~Mesh();

	Mesh& operator=(const Mesh& mesh) = delete;
	Mesh& operator=(Mesh&& mesh);
};

struct Model
{
	std::vector<Mesh> meshes;

	Model();
	Model(const Model& model) = delete;
	Model(Model&& model);
	~Model();

	Model& operator=(const Model& model) = delete;
	Model& operator=(Model&& model);
};


std::shared_ptr<Image> load_image(fs::path path);
void unload_image(std::shared_ptr<Image>& image);

Model* load_model(fs::path path, std::string name, unsigned int pFlags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
void unload_model(std::string name);
Model* get_model(std::string name);
