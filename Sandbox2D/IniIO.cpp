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
	std::vector<std::string> iniFile;
	iniFile.push_back("[START]");
	file.push_back("[END]");

	Settings settings;
	Sector sector;

	for (auto line : file)
	{
		// Skip line if comment
		if (line.at(0) == ';' || line.at(0) == '#') continue;

		std::string nextSectorName = "";

		// Check if a new sector is found
		if (line.at(0) == '[')
		{
			settings[nextSectorName] = sector;
			nextSectorName = Split(Split(line, "[")[1], "]")[0];

			sector.clear();
		}
		else
		{
			const auto keyValuePair = Split(line, "=");
			sector[keyValuePair[0]] = keyValuePair[1];
		}

	}

	_mappedFile = settings;
}


