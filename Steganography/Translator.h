#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <stdint.h>
#include <algorithm>
#include "ColourStruct.h"
class Translator
{
public:
	Translator();
	~Translator();

	void setRGBA(int R, int G, int B, int A);
	std::vector<ColourStruct> encode(std::vector<uint8_t> byteVec, std::vector<ColourStruct> pixelVec);
	std::vector<uint8_t> decode(std::vector<ColourStruct> pixelVec);

private:
	int _rBits, _gBits, _bBits, _aBits;
};