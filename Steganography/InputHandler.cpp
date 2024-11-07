#include "InputHandler.h"



InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

void InputHandler::setImagePath() {
	std::string coverImagePath;
	bool fileExists = false;
	bool correctEnding = false;

	while (!fileExists || !correctEnding){
		std::cout << "Please enter the path of the image to use" << std::endl;
		getline(std::cin, coverImagePath);

		// Check that the file exists and is accessible
		std::ifstream f(coverImagePath.c_str());
		fileExists = f.good();
		f.close();

		// Check that the file ends with one of the supported file extensions
		// If the length of the string is less than 4 characters, then there's no way it can have the correct extension, so fail before checking
		correctEnding = coverImagePath.size() > 4 && (coverImagePath.compare(coverImagePath.length() - 4, 4, ".bmp") || coverImagePath.compare(coverImagePath.length() - 4, 4, ".png"));

		// Display messages error messages if needed
		if (!fileExists) {
			std::cout << "The file you entered was not found, please try again.\n";
		}
		else if (!correctEnding) {
			std::cout << "Only images ending with .png and .bmp are accepted, please try again.\n";
		}
	}
	this->_imagePath = coverImagePath;
}

void InputHandler::setSourceFilePath() {
	std::string sourceFilePath;
	bool fileExists = false;

	while (!fileExists) {
		std::cout << "Enter the file location for the source file." << std::endl;
		getline(std::cin, sourceFilePath);

		// Check that the file exists and is accessible
		std::ifstream f(sourceFilePath.c_str());
		fileExists = f.good();
		f.close();

		// Display an error message if needed
		if (!fileExists) {
			std::cout << "This file path does not exist or is currently inccessible, please try again.\n";
		}
	}
	this->_sourceFilePath = sourceFilePath;
}

void InputHandler::setConcealmentSettings() {
	std::string cR, cG, cB, cA; // String representations of the concealment settings
	int iR = -1; int iG = -1; int iB = -1; int iA = -1; // The numerical values that wil be used; by default they -1 which is invalid
	bool validSettings = false;

	while (!validSettings) {
		std::cout << "Enter values for nR, nG, nB and nA.\n All values must be between 0 and 8.\n At least one value must be greater than 0" << std::endl;
		
		// Attempt to convert the text given by the user into numbers.
		try {
			std::cout << "nR" << std::endl;
			getline(std::cin, cR);
			iR = std::stoi(cR);

			std::cout << "nG" << std::endl;
			getline(std::cin, cG);
			iG = std::stoi(cG);

			std::cout << "nB" << std::endl;
			getline(std::cin, cB);
			iB = std::stoi(cB);

			std::cout << "nA" << std::endl;
			getline(std::cin, cA);
			iA = std::stoi(cA);
		}
		// If the conversiion to an int failed, then it means a bad value was given. Display the error message and reset the values
		catch (const std::invalid_argument) {
			std::cout << "Please only enter numbers from 0 to 8" << std::endl;
			iR = -1; iG = -1; iB = -1; iA = -1; // Set values to all be invalid so they all need to be reset
		}

		// ensure that all values are within 0 and 8, and the total is above 1
		validSettings =
			iR >= 0 && iR <= 8 &&
			iG >= 0 && iG <= 8 &&
			iB >= 0 && iB <= 8 &&
			iA >= 0 && iA <= 8 &&
			iA + iG + iB + iA != 0;

		// If the settings are not valid, inform the user before the loop restarts
		if (!validSettings) {
			std::cout << "Please enter values between 0 and 8, with at least one being 1 or greater" << std::endl;
			std::cout << "You entered: " << cR << " " << cG << " " << cB << " " << cA << std::endl;
		}
	}
	_nR = iR; _nG = iG; _nB = iB; _nA = iA;
}

void InputHandler::setConcealing() {
	bool validResponse = false;
	std::string userResponse;

	while (!validResponse) {
		std::cout << "Enter 0 if you wish to conceal a file or 1 if you wish to extract a file" << std::endl;
		getline(std::cin, userResponse);

		if (userResponse == "0") {
			validResponse = true;
			_concealing = true;
		}
		else if (userResponse == "1") {
			validResponse = true;
			_concealing = false;
		}
		else {
			std::cout << "Input: " << userResponse << " not recognised." << std::endl;
		}
	}
}
