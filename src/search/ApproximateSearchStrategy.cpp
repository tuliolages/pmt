#include "ApproximateSearchStrategy.h"

ApproximateSearchStrategy::ApproximateSearchStrategy(int editDistance) {
	this->editDistance = editDistance;
}

ApproximateSearchStrategy::~ApproximateSearchStrategy() {
	
}

int ApproximateSearchStrategy::phi(char patternChar, char textChar) {
	if (patternChar == textChar) {
		return 0;
	} else {
		return 1;
	}
}
