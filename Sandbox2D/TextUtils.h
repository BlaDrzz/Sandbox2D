#pragma once

inline std::string Indent(const int amount, const int depth = 4)
{
	return std::string(amount * depth, ' ');
}

// TODO: Create generic
inline std::string AddZeroLessThanTen(int n)
{
	return n < 10 ? "0" + std::to_string(n) : std::to_string(n);
}

inline std::string TimeToString(const tm time)
{
	return AddZeroLessThanTen(time.tm_hour) + ":" +
		AddZeroLessThanTen(time.tm_min) + ":" +
		AddZeroLessThanTen(time.tm_sec);
}

inline void Split(std::string s, std::string const &delim, std::vector<std::string>* out)
{
	size_t pos(0);
	while ((pos = s.find(delim)) != std::string::npos) {
		const auto token = s.substr(0, pos);
		out->push_back(token);
		s.erase(0, pos + delim.length());
	}
	out->push_back(s);
}

inline std::vector<std::string> Split(std::string const s, std::string const &delim)
{
	std::vector<std::string> elements;
	Split(s, delim, &elements);
	return elements;
}

inline std::vector<std::string> FileToVec(const std::string path)
{
	std::vector<std::string> result;

	std::ifstream file;
	std::string line;

	file.open(path);
	while (std::getline(file, line))
	{
		result.push_back(line);
	}

	file.close();

	return result;
}

inline void VecToFile(const std::string path, std::vector<std::string> data)
{
	std::ofstream file;
	file.open(path);
	for (const auto& line : data)
	{
		file << line << std::endl;
	}
	file.close();
}

/**
 * \brief removes spaces on the left side of an asci string
 * @param s referenced string to trim from
 */
inline void LtrimByReference(std::string &s)
{
	s.erase(s.begin(), std::find_if(
		s.begin(), 
		s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))
	));
}

/**
* \brief removes spaces on the left side of an asci string
* @param s referenced string to trim from
*/
inline void RtrimByReference(std::string &s)
{
	s.erase(std::find_if(
		s.rbegin(), 
		s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))
	).base(), s.end());
}

/**
* \brief removes spaces on the left side of an asci string
* @param s referenced string to trim from
*/
inline void TrimByReference(std::string &s)
{
	LtrimByReference(s);
	RtrimByReference(s);
}

/**
* \brief removes spaces on the left side of an asci string, and returns it
* @param s string to trim
* @return a string without spaces on either ends
*/
inline std::string Trim(std::string s)
{
	TrimByReference(s);
	return s;
}