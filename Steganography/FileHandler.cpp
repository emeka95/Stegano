#include "FileHandler.h"



FileHandler::FileHandler()
{
}


FileHandler::~FileHandler()
{
}

void FileHandler::readFile(std::string filePath)
{
	std::vector<uint8_t> byteVec = std::vector<uint8_t>();

	// Variable for temporarily holding the newest byte to be read
	char temp;
	std::ifstream is(filePath, std::ios::binary);
	
	// Read bytes until the ifstream reaches its end, then close the stream
	while (is.get(temp)) {
		byteVec.push_back(static_cast<uint8_t>(temp));
	}
	is.close();

	_bytes = byteVec;
}

void FileHandler::writeFile(std::string filePath)
{
	// Open a stream to the given file path in binary mode
	std::ofstream stream;
	stream.open(filePath, std::ios::binary);

	// Write the entire vector into the filepath then close the stream
	stream.write((char *)_bytes.data(), _bytes.size());
	stream.close();
}

std::vector<uint8_t> FileHandler::getBytes()
{
	return _bytes;
}

void FileHandler::setBytes(std::vector<uint8_t> bytes)
{
	_bytes = bytes;
}
