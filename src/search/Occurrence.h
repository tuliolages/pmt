#ifndef OCCURRENCE_H
#define OCCURRENCE_H

struct Occurrence {
	int lineNumber;
	int position;
	int error;
	Occurrence(int lineNumber, int position, int error=0);
};

#endif
