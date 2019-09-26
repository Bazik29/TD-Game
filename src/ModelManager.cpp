#include "ModelManager.hpp"

#include <iostream>

TextureGL::TextureGL()
{
	std::cout << "TextureGL()\n";

	this->id = 0;
	this->type = TextureGLType::DIFFUSE;
}

TextureGL::TextureGL(const TextureGL& texture)
{
	std::cout << "TextureGL(const TextureGL &texture)\n";
	this->id = texture.id;
	this->type = texture.type;
}

TextureGL::~TextureGL()
{
	std::cout << "~TextureGL()\n";
}

TextureGL& TextureGL::operator=(const TextureGL& texture)
{
	std::cout << "TextureGL& operator= (const TextureGL &texture)\n";
	this->id = texture.id;
	this->type = texture.type;
	return *this;
}


Material::Material()
{
	std::cout << "Material()\n";
}

Material::Material(const Material& material)
{
	std::cout << "Material(const Material &material)\n";
	this->textures = material.textures;
}

Material::Material(std::vector<TextureGL>& textures)
{
	std::cout << "Material(std::vector<TextureGL> &textures): " << textures.size() << std::endl;
	this->textures = textures;
}

Material::~Material()
{
	std::cout << "~Material(): " << textures.size() << std::endl;
	this->textures.clear();
}

Material& Material::operator=(const Material& material)
{
	std::cout << "Material& operator= (const Material &material)\n";
	this->textures.clear();
	this->textures = material.textures;
	return *this;
}


Mesh::Mesh()
{
	std::cout << "Mesh()\n";
	this->VAO = 0;
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Material& material)
{
	std::cout << "Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, Material &material)\n";
	this->vertices = vertices;
	this->material = material;
	this->indices = indices;
}

Mesh::~Mesh()
{
	std::cout << "~Mesh()\n";
	this->vertices.clear();
	this->indices.clear();
}

GLuint Mesh::getVAO()
{
	return this->VAO;
}

Mesh& Mesh::operator=(const Mesh& mesh)
{
	std::cout << "Mesh& operator=(const Mesh& mesh)\n";
	this->VAO = mesh.VAO;
	this->vertices = mesh.vertices;
	this->material = mesh.material;
	this->indices = mesh.indices;
	return *this;
}


Model::Model()
{
	std::cout << "Model::Model()\n";
	this->meshes = nullptr;
}

Model::Model(std::vector<Mesh>* meshes)
{
	std::cout << "Model::Model(std::vector<Mesh>* meshes)\n";
	this->meshes = meshes;
}

Model::~Model()
{
	std::cout << "Model::~Model()\n";
}

Model& Model::operator=(const Model& model)
{
	std::cout << "Model& operator=(const Model& model)\n";
	this->meshes = model.meshes;
	return *this;
}


ModelManager::ModelManager()
{
	this->imgMng = new ImageManager;
}

ModelManager::~ModelManager()
{
	delete this->imgMng;
}

void ModelManager::load(std::string name, fs::path path, unsigned int pFlags)
{
	if (model_cash.find(name) != model_cash.end())
		return;

	tmpPath = path;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path.string().c_str(), pFlags);
	if (!scene)
		throw std::runtime_error(importer.GetErrorString());


	std::vector<Mesh>* meshes = new std::vector<Mesh>;
	processNode(scene->mRootNode, scene, meshes);

	model_cash.emplace(name, Model(meshes));
}

const Model& ModelManager::getModel(std::string name)
{
	auto search = model_cash.find(name);
	if (search == model_cash.end())
		throw std::runtime_error("Model \"" + name + "\" not loaded!");

	return search->second;
};

void ModelManager::processNode(const aiNode* node, const aiScene* scene, std::vector<Mesh>* meshes)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
		meshes->push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));

	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene, meshes);
}

Mesh ModelManager::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;

		vertex.Position = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}


	// processMaterial
	aiMaterial* aimaterial = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<TextureGL> textures;
	// aiTextureType_DIFFUSE, aiTextureType_SPECULAR, aiTextureType_HEIGHT, aiTextureType_AMBIENT
	for (unsigned int i = 0; i < aimaterial->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString str;
		aimaterial->GetTexture(aiTextureType_DIFFUSE, i, &str);


		TextureGL texture;
		texture.id = loadTextureGL(str.C_Str());
		texture.type = TextureGLType::DIFFUSE;
		textures.push_back(texture);
	}

	std::cout << "return Mesh(vertices, indices, Material(textures))\n";
	return Mesh(vertices, indices, Material(textures));
}

GLuint ModelManager::loadTextureGL(const char* name)
{
	fs::path path = tmpPath.parent_path().string() + "\\" + name;
	std::cout << "---load TEXTURE: " << path << std::endl;

	auto search = texture_cash.find(path);
	if (search != texture_cash.end())
	{
		std::cout << "---TEXTURE already loaded\n";
		return search->second;
	}
	std::cout << "---TEXTURE loading..\n";
	const Image* img = imgMng->load(path);

	GLuint textureID;
	gl::GenTextures(1, &textureID);
	gl::BindTexture(gl::TEXTURE_2D, textureID);

	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB, img->x, img->y, 0, gl::BGR, gl::UNSIGNED_BYTE, img->data);

	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);

	texture_cash.emplace(path, textureID);
	return textureID;
}

