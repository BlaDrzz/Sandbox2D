#include "../stdafx.h"

IniReader::IniReader(std::string path)
{
	load(path);
}


bool IniReader::load(std::string& path)
{
	if (path == _path)
	{
		LogWarning("Tried to load " + path + " again. Using cached file instead");
		return true;
	}

	_fileCache = FileToVec(path);
	_fileUpdated = true;
	_path = path;

	if (_fileCache.empty())
	{
		LogError("Error reading " + path + ".");
		return false;
	}
	return true;
}

std::unordered_map<std::string, std::string> IniReader::parse()
{
	if (!_iniCache.empty() && !_fileUpdated)
	{
		LogWarning("Tried to parse " + _path + " again without loading a new file, returning cached ini instead.");
		return _iniCache;
	}

	for (const auto& line : _fileCache)
	{
		if (line.empty())		continue;
		if (line.at(0) == ';')	continue;
		if (line.find('=') != std::string::npos)
		{
			const auto keyValue = Split(line, "=");
			_iniCache[Trim(keyValue.at(0))] = Trim(keyValue.at(1));
		}
	}

	return _iniCache;
}

std::string IniReader::stringify()
{
	if (_iniCache.empty())
	{
		return "";
	}

	std::stringstream ss;
	ss << _path << std::endl;
	for (const auto& line : _iniCache)
	{
		ss << line.first << ":" << line.second << std::endl;
	}

	return ss.str();
}

