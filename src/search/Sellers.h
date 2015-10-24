#include <vector>
#include "ApproximateSearchStrategy.h"
#include "Occurrence.h"

class Sellers : ApproximateSearchStrategy {
public:
	Sellers(int editDistance);
	virtual std::vector<Occurrence> search(char* pattern, char* inputFile);
	virtual ~Sellers();
};