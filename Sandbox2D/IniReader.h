#pragma once
#include <unordered_map>

class IniReader
{
public:
	IniReader() {}

	/**
	 * \brief creates an iniReader and loads the file at path 
	 * @param path: file's location
	 */
	IniReader(std::string path);
	~IniReader() {}

	/**
	 * \brief Loads a file and parses it into an std::vector
	 * @param path: file's location
	 * @return true if the file was loaded successfully, false if there was an error fetching the file, or the file is empty.
	 */
	bool load(std::string &path);

	/**
	 * \brief Parses the previously loaded ini file into a key-value unordered_map
	 * @return an associative array
	 */
	std::unordered_map<std::string, std::string> parse();

	
	/**
	 * \brief turns the cached ini into a string, ignoring comments and empty lines
	 * @return a stringified version of the ini
	 */
	std::string stringify();

private:
	bool _fileUpdated = false;
	std::string _path = "";
	std::vector<std::string> _fileCache;
	std::unordered_map<std::string, std::string> _iniCache;
};

