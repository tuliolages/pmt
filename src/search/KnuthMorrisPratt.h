#ifndef KMP_H
#define KMP_H

#include <vector>

#include "ExactSearchStrategy.h"
#include "Occurrence.h"
#include "../input/FileReader.h"

class KnuthMorrisPratt : public ExactSearchStrategy {
public:
	KnuthMorrisPratt();
	virtual ~KnuthMorrisPratt();
	virtual std::vector<Occurrence> search(char* pattern, char* inputFile);
private:
	int* initNext(char* pattern, int patternLength);
	void readFromFile(FileReader &fr, int patternLength, char* buffer, int &bufSize);
	char getTextAt(int index);

	char* currentBuffer;
	int currentBufferSize;
	char* nextBuffer;
	int nextBufferSize;
};

#endif
