#pragma once
#include <stdio.h>
#include <memory.h>
#include <malloc.h>

class FileTools {
private:
	char* m_fileSource;
public:
	char* LoadFile(const char* path);
};