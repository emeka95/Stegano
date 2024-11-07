#include "Translator.h"



Translator::Translator()
{
}


Translator::~Translator()
{
}

void Translator::setRGBA(int R, int G, int B, int A)
{
	_rBits = R;
	_gBits = G;
	_bBits = B;
	_aBits = A;
}

std::vector<ColourStruct> Translator::encode(std::vector<uint8_t> byteVec, std::vector<ColourStruct> pixelVec) {
	// The resulting vector that wil be returned when this function is finished
	std::vector<ColourStruct> result = std::vector<ColourStruct>();

	// The first 4 bytes should represent the size of byteVec as an unsigned 32 bit int, these must also be encoded
	int bytesToEncode = byteVec.size() + 4;

	// Check if pixelVec is large enough to store all data given the concealment parameters
	// 4 extra bytes of "breathing room" have been given to eliminate issues that may come from partially encoded bytes
	if ((4 + bytesToEncode) * 8 > pixelVec.size() * (_rBits + _gBits + _bBits + _aBits)) {
		// If this conditions is not met, encoding the byteVec will fail, so print the error and return an empty vector
		std::cout << "The chosen image does not contain enough pixels to fully conceal the required data with the given concealment parameters" << std::endl;
		return result;
	}

	// get size of byteVec and prepend size of bytevec as first 4 bytes
	unsigned int noOfBytes = byteVec.size();
	// The first 32 bits that are encoded should be the size byteVec. This must be split across four 8-bit entries
	// Pushing back and then rotating should be faster than inserting at the beginning which requires copying everything 4 times
	uint8_t size1 = (noOfBytes >> 24);
	uint8_t size2 = (noOfBytes >> 16) & 0b11111111;
	uint8_t size3 = (noOfBytes >> 8) & 0b11111111;
	uint8_t size4 = noOfBytes & 0b11111111;
	byteVec.push_back(size1);
	byteVec.push_back(size2);
	byteVec.push_back(size3);
	byteVec.push_back(size4);
	std::rotate(byteVec.rbegin(), byteVec.rbegin() + 4, byteVec.rend());
	noOfBytes += 5; // Account for the 4 bytes just added
	byteVec.push_back(0); // Add a dummy byte at the end to prevent indexing issues

	// create variables to temporarily store the values of every pixel as the loop goes along
	unsigned int newR, newG, newB, newA;
	// Track the number of bytes that have been converted so far
	unsigned int bytesConverted = 0;
	// Create a 32 bit buffer to temporarily hold data from byteVec
	unsigned int buffer = 0;
	// Create a tracker for how many bits in the buffer are currently relevant
	int relevantBits = 0;

	// Loop through the byteVec, and convert every single byte
	// The final pixel may be partially messed up, but that should not be a problem since the 'wrong' bits won't be read
	while (bytesConverted < noOfBytes || relevantBits > 0) {

		// Red
		// If the buffer has less than 8 relevant bits, then add more bits to it
		if (relevantBits < 8 && bytesConverted < noOfBytes) {
			buffer <<= 8; // Free up the lowest 8 bits of the buffer
			buffer += byteVec[bytesConverted++]; // Add in the current byte to fill up those 8 bits, and increment to the next byte
			relevantBits += 8; // keep track of number of relevant bits
			buffer &= ((1 << relevantBits) - 1); // Zero out any leading bits that are irrelevant
		}
		// Assign the leading relevant rBits bits of the buffer to newR
		//newR = buffer >> (relevantBits - _rBits);
		newR = (buffer & ((1 << relevantBits) - 1)) >> (relevantBits - _rBits);
		relevantBits -= _rBits; // Lower the counter of relevant bits as appropriate

		// Green
		// If the buffer has less than 8 relevant bits, then add more bits to it
		if (relevantBits < 8 && bytesConverted < noOfBytes) {
			buffer <<= 8; // Free up the lowest 8 bits of the buffer
			buffer += byteVec[bytesConverted++]; // Add in the current byte to fill up those 8 bits, and increment to the next byte
			relevantBits += 8; // keep track of number of relevant bits
			buffer &= ((1 << relevantBits) - 1); // Zero out any leading bits that are irrelevant
		}
		// Assign the leading relevant gBits bits of the buffer to newG
		newG = (buffer & ((1 << relevantBits) - 1)) >> (relevantBits - _gBits);
		relevantBits -= _gBits; // Lower the counter of relevant bits as appropriate

		// Blue
		// If the buffer has less than 8 relevant bits, then add more bits to it
		if (relevantBits < 8 && bytesConverted < noOfBytes) {
			buffer <<= 8; // Free up the lowest 8 bits of the buffer
			buffer += byteVec[bytesConverted++]; // Add in the current byte to fill up those 8 bits, and increment to the next byte
			relevantBits += 8; // keep track of number of relevant bits
			buffer &= ((1 << relevantBits) - 1); // Zero out any leading bits that are irrelevant
		}
		// Assign the leading relevant bBits bits of the buffer to newG
		newB = (buffer & ((1 << relevantBits) - 1)) >> (relevantBits - _bBits);
		relevantBits -= _bBits; // Lower the counter of relevant bits as appropriate

		// Alpha
		// If the buffer has less than 8 relevant bits, then add more bits to it
		if (relevantBits < 8 && bytesConverted < noOfBytes) {
			buffer <<= 8; // Free up the lowest 8 bits of the buffer
			buffer += byteVec[bytesConverted++]; // Add in the current byte to fill up those 8 bits, and increment to the next byte
			relevantBits += 8; // keep track of number of relevant bits
			buffer &= ((1 << relevantBits) - 1); // Zero out any leading bits that are irrelevant
		}
		// Assign the leading relevant aBits bits of the buffer to newG
		newA = (buffer & ((1 << relevantBits) - 1)) >> (relevantBits - _aBits);
		relevantBits -= _aBits; // Lower the counter of relevant bits as appropriate

		// Add a new pixel to the result based on these new rgba values
		result.push_back(ColourStruct{ newR, newG, newB, newA });
	}

	// merge vector of lower bits with pixelVec
	for (int i = 0; i < result.size(); i++) {
		// Clear out lowest _nBits of each channel in pixelVec and put that into result
		// result should already hold the correct values for these lower bits
		result[i].r = (pixelVec[i].r &~((1 << _rBits) - 1)) | result[i].r;
		result[i].g = (pixelVec[i].g &~((1 << _gBits) - 1)) | result[i].g;
		result[i].b = (pixelVec[i].b &~((1 << _bBits) - 1)) | result[i].b;
		result[i].a = (pixelVec[i].a &~((1 << _aBits) - 1)) | result[i].a;
	}

	return result;
}

std::vector<uint8_t> Translator::decode(std::vector<ColourStruct> pixelVec) {
	// Prepare empty vector that should hold results
	std::vector<uint8_t> result = std::vector<uint8_t>();

	// Prepare useful objects for decoding
	// The 64 bit buffer will hold the data currently being worked on
	unsigned long long buffer = 0; // A simple unsigned long is not gauranteed to be 64 bits which caused major problems before
								   // relevantBits will track how many bits in buffer are currently relevant
	int relevantBits = 0;
	// currentPixel will track which pixel is currently being read
	unsigned int currentPixel = 0;
	// get size of pixelVec
	unsigned int size = pixelVec.size();
	// The number of bytes that have been extracted from pixelVec (excluding the first 4 indicating size)
	unsigned int bytesRead = 0;

	// Start by reading 32 bit into the buffer (or as clsoe as possible)
	// This will inform determine how many bytes need to be read afterwards
	while (relevantBits < 32) {
		buffer <<= _rBits;
		buffer += pixelVec[currentPixel].r & ((1 << _rBits) - 1);
		relevantBits += _rBits;
		buffer <<= _gBits;
		buffer += pixelVec[currentPixel].g & ((1 << _gBits) - 1);
		relevantBits += _gBits;
		buffer <<= _bBits;
		buffer += pixelVec[currentPixel].b & ((1 << _bBits) - 1);
		relevantBits += _bBits;
		buffer <<= _aBits;
		buffer += pixelVec[currentPixel++].a & ((1 << _aBits) - 1);
		relevantBits += _aBits;
	}

	// Translate those 32 bits into an unsigned integer
	unsigned int bytesToRead = buffer >> (relevantBits - 32); // Take the 32 leading relevant bits from the buffer
	std::cout << "Bytes to read: " << bytesRead << std::endl;
	// Then clear those bits out
	relevantBits -= 32;
	buffer &= ((1 << relevantBits) - 1);

	// check if this amount of data can still be extracted
	if (bytesToRead * 8 > ((size - currentPixel) * (_rBits + _gBits + _bBits + _aBits)) + relevantBits) {
		// In this case, there is o way to get bytesToRead bytes out of the remainder of pixelVec, so the function MUST fail
		std::cout << "The pixel vector/concealment settings given make it impossible to extract the desired amount of data." << std::endl;
		return result;
	}

	// Keep reading until that amount of bytes have been read (ignoring the 32 bits that indicated size)
	while (bytesRead < bytesToRead)
	{
		buffer <<= _rBits; // Make space in the lowest _rBits bits in buffer
		buffer |= (pixelVec[currentPixel].r & ((1 << _rBits) - 1)); // fill these empty bits with the lowest _rBits of the current pixel
		relevantBits += _rBits; // increase the count of relevant bits to reflect this change

		buffer <<= _gBits; // Make space in the lowest _gBits bits in buffer
		buffer |= (pixelVec[currentPixel].g & ((1 << _gBits) - 1)); // fill these empty bits with the lowest _gBits of the current pixel
		relevantBits += _gBits; // increase the count of relevant bits to reflect this

		buffer <<= _bBits; // Make space in the lowest _bBits bits in buffer
		buffer |= (pixelVec[currentPixel].b & ((1 << _bBits) - 1)); // fill these empty bits with the lowest _bBits of the current pixel
		relevantBits += _bBits; // increase the count of relevant bits to reflect this change

		buffer <<= _aBits; // Make space in the lowest _aBits bits in buffer
		buffer |= (pixelVec[currentPixel].a & ((1 << _aBits) - 1)); // fill these empty bits with the lowest _aBits of the current pixel
		relevantBits += _aBits; // increase the count of relevant bits to reflect this change

		// As long as there are enough relevant bits in the buffer to make a full byte, place them all into the result vector
		while (relevantBits >= 8) {
			uint8_t newByte = (buffer >> (relevantBits - 8)) & 0b11111111;
			result.push_back(newByte);
			relevantBits -= 8;
			bytesRead++;
		}

		// Lastly, increment the pixel counter
		currentPixel++;
	}
	
	return result;
}
