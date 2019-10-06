#include "Model.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#include <utility>

#include <string>

Image::Image()
{
	std::cout << "Image()\n";
	path = "default";
	data = nullptr;
	x = 0;
	y = 0;
	channels = 0;
}

Image::Image(fs::path path, unsigned char* data, unsigned int x, unsigned int y, unsigned int channels)
{
	std::cout << "Image(fs::path path, unsigned char* data, unsigned int x, unsigned int y, unsigned int channels)\n";

	this->path = path;
	this->data = data;
	this->x = x;
	this->y = y;
	this->channels = channels;
}

Image::Image(Image&& image)
{
	std::cout << "Image(Image&& image)\n";
	this->path = image.path;
	this->data = image.data;
	this->x = image.x;
	this->y = image.y;
	this->channels = image.channels;

	image.path = "default";
	image.data = nullptr;
}

Image::~Image()
{
	std::cout << "~Image()\n";
}

Image& Image::operator=(Image&& image)
{
	std::cout << "Image& operator=(Image&& image)\n";
	if (&image == this)
		return *this;

	this->path = image.path;
	this->data = image.data;
	this->x = image.x;
	this->y = image.y;
	this->channels = image.channels;

	image.path = "default";
	image.data = nullptr;

	return *this;
}



Material::Material()
{
	std::cout << "Material()\n";
}

Material::Material(Material&& material):
	textures(std::move(material.textures))
{
	std::cout << "Material(Material&& material)\n";
}

Material::~Material()
{
	std::cout << "~Material()\n";
	this->textures.clear();
}

Material& Material::operator=(Material&& material)
{
	std::cout << "Material& operator=(Material&& material)\n";
	if (&material == this)
		return *this;

	this->textures.clear();
	this->textures = std::move(material.textures);

	return *this;
}


Mesh::Mesh()
{
	std::cout << "Mesh()\n";
}

Mesh::Mesh(Mesh&& mesh) :
	vertices(std::move(mesh.vertices)), indices(std::move(mesh.indices)), material(std::move(mesh.material))
{
	std::cout << "Mesh(Mesh&& mesh)\n";
}

Mesh::~Mesh()
{
	std::cout << "~Mesh()\n";
	this->vertices.clear();
	this->indices.clear();
}

Mesh& Mesh::operator=(Mesh&& mesh)
{
	std::cout << "Mesh& operator=(Mesh&& mesh)\n";
	if (&mesh == this)
		return *this;

	this->vertices = std::move(mesh.vertices);
	this->indices = std::move(mesh.indices);
	this->material = std::move(mesh.material);

	return *this;
}


Model::Model()
{
	std::cout << "Model()\n";
}

Model::Model(Model&& model) :
	meshes(std::move(model.meshes))
{
	std::cout << "Model(Model&& model)\n";
}

Model::~Model()
{
	std::cout << "~Model()\n";
}

Model& Model::operator=(Model&& model)
{
	std::cout << "Model& operator=(Model&& model)\n";
	if (&model == this)
		return *this;

	this->meshes = std::move(model.meshes);
	return *this;
}



std::map<fs::path, Image> images_map;

Image* load_image(fs::path path)
{
	auto search = images_map.find(path);
	if (search != images_map.end())
		return &search->second;

	int x, y, n;
	unsigned char* data = stbi_load(path.string().c_str(), &x, &y, &n, 0);

	auto res = images_map.try_emplace(path, path, data, x, y, n);

	return &res.first->second;
}

void unload_image(fs::path path)
{
	auto search = images_map.find(path);
	if (search == images_map.end())
		return;

	stbi_image_free(search->second.data);

	images_map.erase(search);
}

void unload_image(Image* image)
{
	unload_image(image->path);
}



std::map<std::string, Model> models_map;

fs::path tmpPath;

Mesh processMesh(aiMesh* mesh, const aiScene* scene)
{
	Mesh tmp_mesh;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex v;
		v.position.x = mesh->mVertices[i].x;
		v.position.y = mesh->mVertices[i].y;
		v.position.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			v.texCoords.x = mesh->mTextureCoords[0][i].x;
			v.texCoords.y = mesh->mTextureCoords[0][i].y;
		}

		tmp_mesh.vertices.push_back(v);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			tmp_mesh.indices.push_back(face.mIndices[j]);
	}

	aiMaterial* aimaterial = scene->mMaterials[mesh->mMaterialIndex];

	if (aimaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
	{
		aiString str;
		aimaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);

		fs::path fullpath = tmpPath.parent_path().string() + "\\" + str.C_Str();

		Image* image = load_image(fullpath);

		tmp_mesh.material.textures[TextureType::DIFFUSE] = image;
	}

	return tmp_mesh;
}

void processNode(const aiNode* node, const aiScene* scene, std::string name)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
		models_map[name].meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));

	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene, name);
}

Model* load_model(fs::path path, std::string name, unsigned int pFlags)
{
	auto search = models_map.find(name);
	if (search != models_map.end())
		return &search->second;

	tmpPath = path;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path.string().c_str(), pFlags);

	if (!scene)
		throw std::runtime_error(importer.GetErrorString());

	models_map[name];
	processNode(scene->mRootNode, scene, name);
}

void unload_model(std::string name)
{
	auto search = models_map.find(name);
	if (search == models_map.end())
		return;

	for (auto& mesh : search->second.meshes)
	{
		for (auto& material : mesh.material.textures)
		{
			unload_image(material.second);
		}
		mesh.material.textures.clear();
		mesh.vertices.clear();
		mesh.indices.clear();
	}

	search->second.meshes.clear();

	models_map.erase(search);
}
