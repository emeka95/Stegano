#include "SurfaceHandler.h"

SurfaceHandler::SurfaceHandler()
{
}


SurfaceHandler::~SurfaceHandler()
{
}

void SurfaceHandler::loadSurface(std::string filePath)
{
	//  If an image has already been loaded, don't load another, that should be done by a different surface handler
	if (_loaded) {
		return;
	}

	std::cout << "Image to load: " << filePath << std::endl;

	// Ensure only bmp and png files are loaded
	if (filePath.size() > 4 && (filePath.compare(filePath.length() - 4, 4, ".bmp") || filePath.compare(filePath.length() - 4, 4, ".png"))) {
		_surface = *IMG_Load(filePath.c_str());
		_loaded = true;
		_imagePath = filePath;
		return;
	}
}

void SurfaceHandler::saveSurface(std::string filePath)
// This method allows the file name and type to be sepcified if needed
// If nothing is specified, saveSurface() (the "default") is called instead
{
	if (filePath.compare(filePath.length() - 4, 4, ".bmp") == 0) {
		SDL_SaveBMP(&(this->_surface), filePath.c_str());
	}
	else if (filePath.compare(filePath.length() - 4, 4, ".png") == 0) {
		IMG_SavePNG(&(this->_surface), filePath.c_str());
	}
	else {
		std::cout << "This application can only save .png and .bmp images" << std::endl;
	}
}

void SurfaceHandler::saveSurface() {
	if (_imagePath.compare(_imagePath.length() - 4, 4, ".bmp") == 0) {
		std::cout << "saving as bmp" << std::endl;
		saveSurface("output image.bmp");
	}
	else if (_imagePath.compare(_imagePath.length() - 4, 4, ".png") == 0) {
		std::cout << "saving as png" << std::endl;
		saveSurface("output image.png");
	}
}

ColourStruct SurfaceHandler::getPixel(int x, int y)
{
	// This function should only be called when _loaded is True otherwise it will cause an error
	// It should not be possible for a user to ever do this, so display an error message before the programme fails
	// Returning a default value or otherwise catching this error risks masking a fatal issue
	if (!_loaded) {
		std::cout << "Method SurfaceHandler::getPixel was called before an image was loaded." << std::endl;
	}

	// By default, SDL_Surface.pixels has type void* despite having 32 bit information
	// Therefore, it must be cast as a Uint32 pointer to interpret, but it doesn't need to be kept that way
	Uint32 pixel = ((Uint32 *)_surface.pixels)[(y * _surface.pitch / 4) + x];

	//Split the 32 bit integer into its 8 bit parts
	Uint8 r, g, b, a;
	SDL_GetRGBA(pixel, _surface.format, &r, &g, &b, &a);

	ColourStruct result = ColourStruct();
	result.r = r;
	result.g = g;
	result.b = b;
	result.a = a;

	return result;
}

void SurfaceHandler::setPixel(ColourStruct pixel, int x, int y)
/*	This function should only be called when _loaded is True otherwise it will cause an error
pixel is a colourstruct with the desired rgba values
x and y are the pixel's position in the image horizontally and vertically respectively */
{
	SDL_Surface *surface = &_surface;
	Uint32 *pixelArray = (Uint32*)(_surface.pixels);
	Uint32 *targetPixel = pixelArray + (y * surface->pitch / 4) + (x /* * sizeof *targetPixel */);
	*targetPixel = SDL_MapRGBA(surface->format, pixel.r, pixel.g, pixel.b, pixel.a);
	ColourStruct testPix = getPixel(0, 0);
}

std::vector<ColourStruct> SurfaceHandler::getSurface() {
	auto result = std::vector<ColourStruct>();
	for (int y = 0; y < _surface.h; y++) {
		for (int x = 0; x < _surface.w; x++) {
			result.push_back(getPixel(x, y));
		}
	}
	return result;
}

void SurfaceHandler::setSurface(std::vector<ColourStruct> pixels) {
	int end = pixels.size();
	int width = _surface.w;
	int height = _surface.h;
	for (int i = 0; i < end; i++) {
		setPixel(pixels[i], i % width, i / width);
	}
}
