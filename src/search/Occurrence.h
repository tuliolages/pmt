#ifndef OCCURRENCE_H
#define OCCURRENCE_H

struct Occurrence {
	int lineNumber;
	int position;
	Occurrence(int lineNumber, int position);
};

#endif
