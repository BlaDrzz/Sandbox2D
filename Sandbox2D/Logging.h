#pragma once

#define _LOGPATH "log.txt"

//! Returns a tm struct with timeNow
inline tm TimeNow()
{
	// Generate localtime
	time_t rawTime = time(nullptr);
	tm localTime;
	localtime_s(&localTime, &rawTime);

	return localTime;
}

//! Creates a log
inline bool CreateLog()
{
	std::ofstream log;
	log.open(_LOGPATH);
	log << TimeToString(TimeNow()) << ": " << "---[General Sandbox2D log]---\n";
	log.close();

	return true;
}

//! Appends a message to an already existing file
inline void LogToFile(std::string msg, std::string path)
{
	std::ofstream log;

	log.open(path, std::ios_base::app);
	log << msg << std::endl;
	log.close();
}

//! Logs a message to the console and to logs.txt
inline void Log(std::string msg)
{
	// Prefix message with timestamp
	const std::string timeStampedMessage = TimeToString(TimeNow()) + ": " + msg;

	// Log to console
	std::cout << timeStampedMessage << std::endl;

	// Log to file
	LogToFile(timeStampedMessage, _LOGPATH);
}

//! Logs a message with info prefix
inline void LogInfo(std::string msg)
{
	Log("[INFO] " + msg);
}

//! Logs a message with warning prefix
inline void LogWarning(std::string msg)
{
	Log("[WARNING] " + msg);
}

//! Logs a message with errir prefix
inline void LogError(std::string msg)
{
	Log("[ERROR] " + msg);
}