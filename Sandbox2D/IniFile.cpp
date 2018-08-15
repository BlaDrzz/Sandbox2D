#include "../stdafx.h"

IniFile::IniFile(const std::string path)
{
	load(path);
}


IniFile* IniFile::load(const std::string path)
{
	if (path == _path)
	{
		LogWarning("Tried to load " + path + " again. Using cached file instead");
		return this;
	}

	_fileCache = FileToVec(path);
	_fileUpdated = true;
	_path = path;

	if (_fileCache.empty())
	{
		LogError("Error reading " + path + ".");
		return this;
	}
	return this;
}

IniFile* IniFile::write()
{
	write(_path);

	return this;
}

IniFile* IniFile::write(const std::string path)
{
	_path = path;

	std::vector<std::string> fileVec;
	for (const auto &section : _iniCache)
	{
		fileVec.push_back("[" + section.first + "]");
		for (const auto &value : section.second)
		{
			fileVec.push_back(value.first + "=" + value.second);
		}
	}

	VecToFile(path, fileVec);
	return this;
}

IniFile* IniFile::parse()
{
	if (!_iniCache.empty() && !_fileUpdated)
	{
		LogWarning("Tried to parse " + _path + " again without loading a new file.");
		return this;
	}

	std::string lastSection = "no section";
	auto i = 0;
	for (auto& line : _fileCache)
	{
		i++;

		if (line.empty()) continue;
		
		Trim(line);
		if (line.at(0) == ';') continue;
		if (line.at(0) == '[')
		{
			// Found a new section
			const auto sectionName = line.substr(1, line.find(']') - 1);
			_iniCache[sectionName];
			lastSection = sectionName;
			continue;
		}
		if (line.find('=') != std::string::npos)
		{
			// Found a key-value pair
			const auto keyValue = Split(line, "=");

			if (lastSection == "no section")
			{
				LogWarning("Line " + std::to_string(i) + " does not belong to any section, storing it under 'no section' instead.");
			}
			_iniCache[lastSection][Trim(keyValue.at(0))] = Trim(keyValue.at(1));
			continue;
		}

		LogError("Failed to parse line " + std::to_string(i) + " in file " + _path);
	}

	return this;
}

std::string IniFile::getValue(const std::string section, const std::string key)
{
	try
	{
		return _iniCache.at(section).at(key);
	}
	catch(const std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
		LogError(section + " or " + key + " not found in " + _path);
		return "";
	}
}

IniFile* IniFile::setValue(const std::string section, const Tuple<std::string> kvPair)
{
	_iniCache[section][kvPair.x] = kvPair.y;
	return this;
}

IniFile::IniSection IniFile::getSection(const std::string section)
{
	try
	{
		return _iniCache.at(section);
	}
	catch(const std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
		LogError(section + " does not exist in " + _path + "!");
		return IniSection();
	}
}

IniFile* IniFile::createSection(const std::string section)
{
	_iniCache[section] = IniSection();
	return this;
}

std::string IniFile::stringify()
{
	if (_iniCache.empty())
	{
		return "";
	}

	std::stringstream ss;
	ss << "Reading ini: " + _path + ":" << std::endl;
	for (const auto &section : _iniCache)
	{
		ss << "[" << section.first << "]" << std::endl;
		for (const auto &value : section.second)
		{
			ss << value.first << "=" << value.second << std::endl;
		}
	}

	return ss.str();
}