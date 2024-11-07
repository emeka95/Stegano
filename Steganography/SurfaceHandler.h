#pragma once
#include <SDL.h>
#include <string>
#include <algorithm>
#include "ColourStruct.h"
#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include <vector>

class SurfaceHandler
{
public:
	SurfaceHandler();
	~SurfaceHandler();

	void SurfaceHandler::loadSurface(std::string filePath);
	void SurfaceHandler::saveSurface(std::string filePath);
	void SurfaceHandler::saveSurface();
	ColourStruct SurfaceHandler::getPixel(int x, int y);
	std::vector<ColourStruct> SurfaceHandler::getSurface();
	void SurfaceHandler::setPixel(ColourStruct pixel, int x, int y);

	void SurfaceHandler::setSurface(std::vector<ColourStruct> pixels);


	SDL_Surface _surface;
	std::string _imagePath;
	bool _loaded = false;
};

