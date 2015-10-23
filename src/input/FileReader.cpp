#include <fstream>
#include <iostream>

#include "FileReader.h"

using namespace std;

FileReader::FileReader(char* filePath, int maxBytes)
		: lineCount(1),
			currentReadingPosition(0),
			bufferSize(0),
			maxBytes(maxBytes) {
	this->fileStream = new ifstream(filePath);
	this->buffer = new char[maxBytes];
}

FileReader::~FileReader() {
	this->fileStream->close();

	delete this->fileStream;
	delete this->buffer;
}

char* FileReader::read() {
	int lastBufferSize = this->bufferSize;

	this->fileStream->get(this->buffer, this->maxBytes);
	this->bufferSize = this->fileStream->gcount();

	if (!this->bufferSize) {
		this->fileStream->clear();
		this->fileStream->getline(this->buffer, this->maxBytes); //\r\n\0

		this->bufferSize = 0;
		this->currentReadingPosition = 0;
		++this->lineCount;
	} else {
		this->currentReadingPosition += lastBufferSize;
	}

	return this->buffer;
}

bool FileReader::hasContent() {
	return this->fileStream->good();
}
