#include <string.h>
#include <algorithm>
#include <iostream>
#include <stdio.h>

#include "BoyerMoore.h"
#include "../input/FileReader.h"

#define NUMBER_OF_CHARS 256

using namespace std;

BoyerMoore::BoyerMoore()
	: currentBuffer(0),
		currentBufferSize(0),
		nextBuffer(0),
		nextBufferSize(0) { }

BoyerMoore::~BoyerMoore() {
}

void BoyerMoore::borders(char *pat, int *B) {
	int m = strlen(pat);
	int i;
	B[0] = -1;
	for (i = 1; i <= m; i++)
		B[i] = 0;
	i = 1;
	int j = 0;
	while (i<m) {
		while((i+j)<m && pat[j]==pat[i+j]) {
		cout << "ti" << endl;
			j += 1;
			B[i+j]=j;
		}
		i += (j-B[j]);
		j = std::max(0, B[j]);
	}
}

void BoyerMoore::good_suffix_heuristic(char *pat, int m, int *gs) {
	int Pi [m+1];
	BoyerMoore::borders(pat, Pi);
	int PiR [m+1];
	int i;
	PiR[0] = Pi[m];
	gs[0] = m+1;
	for (i = 1; i < m+1; i++) {
		PiR[i] = Pi[m-i];
		gs[i] = m-Pi[m];
	}
	int j;
	for (i = 1; i < m; i++) {
		j = m-1-PiR[i];
		if (gs[j] > i-PiR[i])
			gs[j] = i-PiR[i];
	}
}

void BoyerMoore::bad_character_heuristic(char *pat, int m, int *bc) {
	int i;
	
	for (i = 0; i < NUMBER_OF_CHARS; i++) {
		bc[i] = -1;
	}
	
	for (i = 0; i < m; i++) {
		bc[(int) pat[i]] = i;
	}
}

void readFromFile2(FileReader &fr, int patternLength, char* buffer, int &bufSize) {
	if (patternLength >= fr.maxBytes) {
		fr.read(buffer, patternLength);
	} else {
		strcpy(buffer, fr.read());
	}

	bufSize = fr.bufferSize;
}

char BoyerMoore::getTextAt(int index) {
	if (index >= this->currentBufferSize) {
		return this->nextBuffer[index - this->currentBufferSize];
	} else {
		return this->currentBuffer[index];
	}
}

vector<Occurrence> BoyerMoore::search(char *pattern, char *inputFile) {
	vector<Occurrence> result;
	FileReader fr(inputFile);
	int bufferLength; //TODO
	int patternLength = strlen(pattern);

	int badCharArray[NUMBER_OF_CHARS];
	bad_character_heuristic(pattern, patternLength, badCharArray);
	int goodSuffixArray[patternLength+1];
	good_suffix_heuristic(pattern, patternLength, goodSuffixArray);

	int cursor = 0;
	int matches = 0;
	int readingPosition = 0;
	int lineCount = 0;
	
	if (patternLength >= fr.maxBytes) {
		this->currentBuffer = new char[patternLength + 1]; // tamanho mínimo de buffer
		this->nextBuffer = new char[patternLength + 1];
		bufferLength = patternLength;
	} else {
		this->currentBuffer = new char[fr.maxBytes]; // tamanho mínimo de buffer
		this->nextBuffer = new char[fr.maxBytes];
		bufferLength = fr.maxBytes;
	}

	while (fr.hasContent()) {
		++lineCount;
		cursor = 0;
		matches = 0;
		readingPosition = 0;

		readFromFile2(fr, bufferLength, this->currentBuffer, this->currentBufferSize);
		if (this->currentBufferSize) {
			readFromFile2(fr, bufferLength, this->nextBuffer, this->nextBufferSize);
		} else {
			this->nextBuffer[0] = '\0';
			this->nextBufferSize = 0;
		}

		while (this->nextBufferSize || cursor + patternLength <= this->currentBufferSize + this->nextBufferSize) {
			int j = patternLength-1;
			while(j>=0 && this->getTextAt(cursor + j)==pattern[j]) {
				j -= 1;
			}
			if (j<0) {
				result.push_back(Occurrence(lineCount, readingPosition + cursor));
				cursor += goodSuffixArray[0];
			} else {
				cursor += std::max(j-badCharArray[this->getTextAt(cursor + j)], goodSuffixArray[j]);
			}

			if (this->nextBufferSize && cursor >= this->currentBufferSize) {
				char* aux = this->currentBuffer;
				this->currentBuffer = this->nextBuffer;
				this->nextBuffer = aux;
				readingPosition = fr.currentReadingPosition;

				readFromFile2(fr, bufferLength, this->nextBuffer, this->nextBufferSize);

				cursor -= this->currentBufferSize;
			}
		}
	}
	
	delete this->currentBuffer;
	delete this->nextBuffer;

	return result;
}
