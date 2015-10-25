#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#include <vector>

#include "ExactSearchStrategy.h"
#include "Occurrence.h"
#include "../input/FileReader.h"

class BoyerMoore : public ExactSearchStrategy {
public:
	BoyerMoore();
	virtual ~BoyerMoore();
	virtual std::vector<Occurrence> search(char* pattern, char* inputFile);
private:
	void borders(char *pattern, int patternLength, int *borderArray);
	void goodSuffixHeuristic(char *pattern, int patternLength, int *gs);
	void badCharacterHeuristic(char *pattern, int patternLength, int *bc);
	void readFromFile(FileReader &fr, int patternLength, char* buffer, int &bufSize);
	char getTextAt(int index);

	char* currentBuffer;
	int currentBufferSize;
	char* nextBuffer;
	int nextBufferSize;
};

#endif
