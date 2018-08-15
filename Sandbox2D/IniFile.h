#pragma once

class IniFile
{
public:
	typedef std::unordered_map<std::string, std::string> IniSection;
	typedef std::unordered_map<std::string, IniSection> Ini;

	IniFile() {}

	/**
	 * \brief creates an iniReader and loads the file at path 
	 * @param path: file's location
	 */
	IniFile(std::string path);

	~IniFile() {}

	/**
	 * \brief Loads a file and parses it into an std::vector
	 * @param path: file's location
	 * @return the IniFile object pointer
	 */
	IniFile* load(std::string path);

	/**
	 * \brief write's a file if the internal path of the ini file is set. If not, use write(path) instead!
	 * @return the IniFile object pointer
	 */
	IniFile* write();


	/**
	 * \brief write's a file to the path.
	 * @param path relative path to write to, including filename
	 * @return the IniFile object pointer
	 */
	IniFile* write(std::string path);

	/**
	 * \brief Parses the previously loaded ini file into a key-value unordered_map
	 * @return the IniFile object pointer
	 */
	IniFile* parse();

	/**
	 * \brief gets a value based on the section and key
	 * @param section the section to look in
	 * @param key the key to retrieve
	 * @return returns the value, or an empty string if the value wasn't found
	 */
	std::string getValue(std::string section, std::string key);

	/**
	 * \brief sets a value based on the section and a keyvalue pair
	 * @param section the section to place the pair under
	 * @param kvPair a Tuple with the key as x, and the value as y
	 * @return the IniFile object pointer
	 */
	IniFile* setValue(std::string section, Tuple<std::string> kvPair);

	/**
	 * \brief get a section of the ini file
	 * @param section the section to retrieve
	 * @return an unordered_map with key-value pairs
	 */
	IniSection getSection(std::string section);

	/**
	 * \brief creates an empty section or removes all keyvalue pairs associated with a given section
	 * @param section the section to create/clear
	 * @return the IniFile object pointer
	 */
	IniFile* createSection(std::string section);
	
	/**
	 * \brief turns the cached ini into a string, ignoring comments and empty lines
	 * @return a stringified version of the ini
	 */
	std::string stringify();

private:
	bool _fileUpdated = false;
	std::string _path = "unnamed.ini";
	std::vector<std::string> _fileCache;

	Ini _iniCache;
};

