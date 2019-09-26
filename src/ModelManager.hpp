#pragma once

#include "gl_core_4_3.hpp"
#include <glm/glm.hpp>

#include "FS.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <map>

#include "ImageMager.hpp"

#include <string>

enum class TextureGLType
{
	DIFFUSE
};


struct TextureGL
{
	GLuint id;
	TextureGLType type;

	TextureGL();
	TextureGL(const TextureGL& texture);
	~TextureGL();

	TextureGL& operator=(const TextureGL& texture);
};


struct Material
{
	std::vector<TextureGL> textures;

	Material();
	Material(const Material& material);
	Material(std::vector<TextureGL>& textures);
	~Material();

	Material& operator=(const Material& material);
};


struct Vertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
};


class Mesh
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	Material material;
	GLuint VAO;

public:
	Mesh();
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Material& material);
	~Mesh();
	Mesh& operator=(const Mesh& mwsh);
	GLuint getVAO();
};


class Model
{
public:
	Model();
	Model(std::vector<Mesh>* meshes);
	~Model();

	Model& operator=(const Model& model);
private:
	std::vector<Mesh>* meshes;
};


class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	void load(std::string name, fs::path path, unsigned int pFlags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	const Model& getModel(std::string name);
private:
	ImageManager* imgMng;
	std::map<std::string, Model> model_cash;
	std::map<fs::path, GLuint> texture_cash;

	void processNode(const aiNode* node, const aiScene* scene, std::vector<Mesh>* meshes);
	Mesh ModelManager::processMesh(aiMesh* mesh, const aiScene* scene);

	GLuint loadTextureGL(const char* name);

	fs::path tmpPath;
};
