#pragma once

#include <string>

struct Image
{
public:
	Image(std::string path) { _path = path; };

private:
	std::string _path;

	friend class GraphicManager;

	Image* _image;
};

