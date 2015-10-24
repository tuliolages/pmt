#include <fstream>

class FileReader {
public:
	FileReader(char *filePath, int maxBytes=1048576);
	~FileReader();
	char* read();
	bool hasContent();
	char* readLine();

	int lineCount;
	int currentReadingPosition;
	char* buffer;
	int bufferSize;
	int maxBytes;
private:
	std::ifstream* fileStream;
};
