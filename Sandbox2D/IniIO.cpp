#include "IniIO.h"


IniIO::IniIO(const std::string path)
{
	readFile(path);
}

IniIO::~IniIO()
{
}

void IniIO::readFile(const std::string path)
{
	auto file = FileToVec(path);

	for (auto line : file)
	{
		Split(line, "[");
	}
}
