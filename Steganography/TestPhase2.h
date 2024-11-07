#pragma once
#include "ColourStruct.h"
#include "SurfaceHandler.h" // May not be needed
#include <iostream>
#include <SDL_image.h>
#include <gtest\gtest.h>
#include <vector>
#include "Translator.h"

TEST(Phase2, TranslateDataIntoPixelAndBackIntoData) {
	bool allSuccess = true;
	// All concealment parameters may be values between 0 and 8 (inclusive)
	// 0/0/0/0 is the only non-valid combination, so start with 0/0/0/1
	int nR, nG, nB, nA;
	nR = 0;
	nG = 0;
	nB = 0;
	nA = 1;

	// 4 Bytes of meaningful data will be concealed in each case
	// The numbers chosen are not significant for this test
	std::vector<uint8_t> bytesToStore = std::vector<uint8_t>();
	bytesToStore.push_back(127);
	bytesToStore.push_back(63);
	bytesToStore.push_back(32);
	bytesToStore.push_back(200);

	// A vector of pixels to be used for concealment. Up to 64 are needed for to conceal 4 bytes (plus 32-bit size data)
	// Fill this with perfectly average 128 128 128 128 pixels
	std::vector<ColourStruct> pixelVec = std::vector<ColourStruct>();
	for (int i = 0; i < 128; i++) {
		pixelVec.push_back(ColourStruct(128, 128, 128, 128));
	}

	// Create translator object
	Translator translator = Translator();

	// create vectors to store result of each cycle
	std::vector<ColourStruct> encodedPixels;
	std::vector<uint8_t> decodedBytes;

	while (nR <= 8) {
		while (nG <= 8) {
			while (nB <= 8) {
				while (nA <= 8) {
					translator.setRGBA(nR, nG, nB, nA);
					encodedPixels = translator.encode(bytesToStore, pixelVec);
					std::cout << nR << nG << nB << nA << "encode complete" << std::endl;
					std::cout << "Vector size: " << encodedPixels.size() << std::endl;
					std::cout << encodedPixels[0].r << " " << encodedPixels[0].g << " " << encodedPixels[0].b << " " << encodedPixels[0].a << std::endl;
					decodedBytes = translator.decode(encodedPixels);
					std::cout << nR << nG << nB << nA << "decode complete" << std::endl;

					std::cout << "Encoded pixels: " << std::endl;
					for each (auto item in encodedPixels) {
						std::cout << item.r << " " << item.g << " " << item.b << " " << item.a << " " << std::endl;
					}

					ASSERT_EQ(decodedBytes[0], bytesToStore[0]);
					ASSERT_EQ(decodedBytes[1], bytesToStore[1]);
					ASSERT_EQ(decodedBytes[2], bytesToStore[2]);
					ASSERT_EQ(decodedBytes[3], bytesToStore[3]);
					std::cout << nR << nG << nB << nA << "Assertions complete" << std::endl;
					nA++;
				}
				nB++;
				nA = 0;
			}
			nG++;
			nB = 0;
		}
		nR++;
		nG = 0;
	}
}