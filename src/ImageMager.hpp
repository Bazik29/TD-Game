#pragma once

#include "FS.hpp"
#include <map>

/*
	������ �������� ������ ����������� (��������, ������� ����� �������)
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
	������ ��� �������� �����������
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
