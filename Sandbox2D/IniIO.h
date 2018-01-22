#pragma once

#include "../stdafx.h"

class IniIO
{
	typedef std::unordered_map<std::string, std::string> Sector;
	typedef std::unordered_map<std::string, Sector> Settings;
public:
	IniIO(const std::string path);
	~IniIO();

	void readFile(std::string path);

	std::string getValue(std::string sector, std::string key) {};
	Sector getSector(std::string sectorName) {};

private:
	Settings _mappedFile;
};

