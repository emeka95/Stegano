#include <iostream>
#include <string>
#include <SDL.h>
#include "ColourStruct.h"
#include "FileHandler.h"
#include "InputHandler.h"
#include "SurfaceHandler.h"
#include "Translator.h"
#include <gtest/gtest.h>
#include "TestPhase1.h"
#include "TestPhase2.h"

void testThisApp(int argc, char** args) {
	::testing::InitGoogleTest(&argc, args);
	RUN_ALL_TESTS();
}

void run() {
	// Get user input
	InputHandler ih = InputHandler();
	ih.setConcealing();
	ih.setImagePath();
	ih.setConcealmentSettings();

	// Load the image
	SurfaceHandler sh = SurfaceHandler();
	sh.loadSurface(ih.getImagePath());

	// Create a file handler object for IO
	FileHandler fh = FileHandler();

	// Create a translator object with the appropriate RGBA settings
	Translator trans = Translator();
	std::cout << "Concealment parameters = " << ih.getnR() << " " << ih.getnG() << " " << ih.getnB() << " " << ih.getnA() << std::endl;
	trans.setRGBA(ih.getnR(), ih.getnG(), ih.getnB(), ih.getnA());

	// Prepare a vector for holding pixels
	std::vector<ColourStruct> pixelVec;

	if (ih.getConcealing()) {
		std::cout << "Concealing" << std::endl;
		ih.setSourceFilePath(); // Get the path of the source file from the user
		fh.readFile(ih.getSourceFilePath()); // Load that source file
		std::cout << "Bytes to encode " << fh.getBytes().size() << std::endl;
		pixelVec = trans.encode(fh.getBytes(), sh.getSurface()); // Encode that data using a pixelvector
		sh.setSurface(pixelVec);
		sh.saveSurface();
	}
	else {
		pixelVec = sh.getSurface(); // Get the vector of pixels in the image
		std::vector<uint8_t> byteVec = trans.decode(pixelVec); // Decode the bytes
		std::cout << "Decode complete" << std::endl;
		fh.setBytes(byteVec); // Decode the image and assign this to the file handler
		std::cout << "Bytes set " << byteVec.size() << std::endl;

		std::cout << std::endl;
		fh.writeFile("output file");
	}
}

int main(int argc, char** args) {

	// Initialise SDL's image handling components
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Failed to initialise SDL; Error: ", SDL_GetError());
		return 1;
	}

	// Initialise and run all tests
	//testThisApp(argc, args);

	// Run the main app
	run();

	
	std::string consoleClosureDelay;
	getline(std::cin, consoleClosureDelay);

	return 0;
}