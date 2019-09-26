#include "ImageMager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <string>

Image::Image()
{
	std::cout << "Image()\n";

	data = nullptr;
	x = 0;
	y = 0;
	channels = 0;
}

Image::Image(unsigned char* data, unsigned int x, unsigned int y, unsigned int channels)
{
	std::cout << "Image(unsigned char* data, unsigned int x, unsigned int y, unsigned int channels)\n";

	this->data = data;
	this->x = x;
	this->y = y;
	this->channels = channels;
}

Image::~Image()
{
	std::cout << "~Image()\n";
}
Image::Image(const Image& image)
{
	std::cout << "Image(const Image& image)\n";
	this->data = image.data;
	this->x = image.x;
	this->y = image.y;
	this->channels = image.channels;
};

Image& Image::operator=(const Image& image)
{
	std::cout << "Image& operator=(const Image& image)\n";
	this->data = image.data;
	this->x = image.x;
	this->y = image.y;
	this->channels = image.channels;

	return *this;
};

ImageManager::ImageManager() {}

ImageManager::~ImageManager() {}

const Image* ImageManager::load(const fs::path& path)
{
	auto search = image_cash.find(path);
	if (search != image_cash.end())
		return &search->second;

	int x, y, n;
	unsigned char* data = stbi_load(path.string().c_str(), &x, &y, &n, 0);

	auto res = image_cash.emplace(path, Image(data, x, y, n));

	return &res.first->second;
}

void ImageManager::unLoad(const fs::path& path)
{
	auto search = image_cash.find(path);
	if (search == image_cash.end())
		return;

	stbi_image_free(search->second.data);
	image_cash.erase(search);
}

void ImageManager::clear()
{
	for (auto& it : image_cash)
	{
		stbi_image_free(it.second.data);
	}
	image_cash.clear();
}

const Image* ImageManager::getImage(const fs::path& path)
{
	auto search = image_cash.find(path);
	if (search == image_cash.end())
		// return nullptr
		throw std::runtime_error("Image \"" + path.string() + "\" not loaded!");

	return &search->second;
}
