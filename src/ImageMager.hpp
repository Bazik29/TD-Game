#pragma once

#include "FS.hpp"
#include <map>

/*
	Хранит основные данные изображения (колормап, размерб число каналов)
*/
struct Image
{
	unsigned char* data;
	unsigned int x;
	unsigned int y;
	unsigned int channels;

	Image();
	Image(const Image& image);
	Image(unsigned char* data, unsigned int x, unsigned int y, unsigned int channels);
	~Image();

	Image& operator=(const Image& image);
};


/*
	Служит для загрузки изображений
*/
class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	const Image* load(const fs::path& path);
	void unLoad(const fs::path& path);
	const Image* getImage(const fs::path& path);
	void clear();

private:
	std::map<fs::path, Image> image_cash;
};
