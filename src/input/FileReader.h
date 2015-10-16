#include <fstream>

class FileReader {
public:
	FileReader(char *filePath, int maxBytes=1024);
	~FileReader();
	char* read();
	bool hasContent();

	int lineCount;
	int currentReadingPosition;
	char* buffer;
	int bufferSize;
	int maxBytes;
private:
	std::ifstream* fileStream;
};
