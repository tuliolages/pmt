#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#include <vector>

#include "ExactSearchStrategy.h"
#include "Occurrence.h"

class BoyerMoore : public ExactSearchStrategy {
public:
	BoyerMoore();
	virtual ~BoyerMoore();
	virtual std::vector<Occurrence> search(char* pattern, char* inputFile);
private:
	void borders(char *pattern, int *B);
	void good_suffix_heuristic(char *pattern, int pattern_length, int *good_suffix_array);
	void bad_character_heuristic(char *pattern, int pattern_lenght, int *bad_character_array);
	char getTextAt(int index);

	char* currentBuffer;
	int currentBufferSize;
	char* nextBuffer;
	int nextBufferSize;
};

#endif
