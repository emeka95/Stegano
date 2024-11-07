#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class FileHandler
{
public:
	FileHandler();
	~FileHandler();

	void readFile(std::string filePath);
	void writeFile(std::string filePath);

	std::vector<uint8_t> getBytes();
	void setBytes(std::vector<uint8_t> bytes);

private:
	std::vector<uint8_t> _bytes;
};

