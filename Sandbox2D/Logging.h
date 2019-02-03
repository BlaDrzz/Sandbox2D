#pragma once

#define _LOGPATH "log.txt"

/**
* \brief Returns a tm struct with timeNow
* @return A tm struct with timeNow
*/
inline tm TimeNow()
{
	// Generate localtime
	time_t rawTime = time(nullptr);
#ifdef _WIN32
	tm localTime;
	localtime_s(&localTime, &rawTime);
    
	return localTime;
#else
	tm* localTime;
	localTime = localtime(&rawTime);
    
	return *localTime;
#endif
}

/**
* \brief Creates a log
* @return A boolean
*/
inline bool CreateLog()
{
	std::ofstream log;
	log.open(_LOGPATH);
	log << TimeToString(TimeNow()) << ": " << "---[General Sandbox2D log]---\n";
	log.close();

	return true;
}

/**
* \brief Appends a message to an already existing file
* @param msg: a string as message
* @param path: a string as path
*/
inline void LogToFile(const std::string msg, const std::string path)
{
	std::ofstream log;

	log.open(path, std::ios_base::app);
	log << msg << std::endl;
	log.close();
}

/**
* \brief Logs a message to the console and to logs.txt
* @param msg
*/
inline void Log(const std::string msg)
{
	// Prefix message with timestamp
	const auto timeStampedMessage = TimeToString(TimeNow()) + ": " + msg;

	// Log to console
	std::cout << timeStampedMessage << std::endl;

	// Log to file
	LogToFile(timeStampedMessage, _LOGPATH);
}

/**
* \brief Logs a message with info prefix
* @param msg: a string as message
*/
inline void LogInfo(const std::string msg)
{
	Log("[INFO] " + msg);
}

/**
* \brief Logs a message with warning prefix
* @param msg: a string as message
*/
inline void LogWarning(const std::string msg)
{
	Log("[WARNING] " + msg);
}

/**
* \brief Logs a message with errir prefix
* @param msg: a string as message
*/
inline void LogError(const std::string msg)
{
	Log("[ERROR] " + msg);
}