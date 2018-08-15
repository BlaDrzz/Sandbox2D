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
	tm localTime;
	localtime_s(&localTime, &rawTime);

	return localTime;
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
* @param smg: a string as message
* @param path: a string as path
*/
inline void LogToFile(std::string msg, std::string path)
{
	std::ofstream log;

	log.open(path, std::ios_base::app);
	log << msg << std::endl;
	log.close();
}

/**
* \brief Logs a message to the console and to logs.txt
* @param smg: a string as message
*/
inline void Log(std::string msg)
{
	// Prefix message with timestamp
	const std::string timeStampedMessage = TimeToString(TimeNow()) + ": " + msg;

	// Log to console
	std::cout << timeStampedMessage << std::endl;

	// Log to file
	LogToFile(timeStampedMessage, _LOGPATH);
}

/**
* \brief Logs a message with info prefix
* @param smg: a string as message
*/
inline void LogInfo(std::string msg)
{
	Log("[INFO] " + msg);
}

/**
* \brief Logs a message with warning prefix
* @param smg: a string as message
*/
inline void LogWarning(std::string msg)
{
	Log("[WARNING] " + msg);
}

/**
* \brief Logs a message with errir prefix
* @param smg: a string as message
*/
inline void LogError(std::string msg)
{
	Log("[ERROR] " + msg);
}