#pragma once
#include <iostream>
#include <string>
#include <fstream>

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void InputHandler::setImagePath();
	void InputHandler::setSourceFilePath();

	void InputHandler::setConcealmentSettings();

	void InputHandler::setConcealing();

	std::string InputHandler::getImagePath() { return this->_imagePath; }
	std::string InputHandler::getSourceFilePath() { return this->_sourceFilePath; }
	
	int InputHandler::getnR() { return _nR; }
	int InputHandler::getnG() { return _nG; }
	int InputHandler::getnB() { return _nB; }
	int InputHandler::getnA() { return _nA; }

	bool InputHandler::getConcealing() { return _concealing; }

private:
	std::string _imagePath;
	std::string _sourceFilePath;
	int _nR, _nG, _nB, _nA;
	bool _concealing;
};

