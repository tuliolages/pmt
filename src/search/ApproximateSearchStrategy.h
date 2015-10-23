#include <vector>
#include "Occurrence.h"

class ApproximateSearchStrategy {
public:
	ApproximateSearchStrategy(int editDistance);
	virtual ~ApproximateSearchStrategy();
	int editDistance;
	virtual std::vector<Occurrence> search(char*pattern, char* inputFile) = 0;
	int phi(char patternChar, char textChar);
};
