#include "FileTools.h"

char* FileTools::LoadFile(const char* path)
{
	FILE* file = fopen(path, "rt");
	fseek(file, 0, SEEK_END);
	unsigned long length = ftell(file);
	char* data = (char*)malloc(length + 1);

	if (!data) {
		fclose(file);

		return 0;
	}
	else {
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		m_fileSource = data;

		return m_fileSource;
	}
}
