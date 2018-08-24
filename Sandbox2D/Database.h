#pragma once
#include "../SQLite/sqlite3.h"

typedef std::unordered_map<std::string, std::string> Row;
typedef std::vector<Row> Table;

class Database
{
public:
	Database(std::string filename);
	~Database();

	Table	fetchAll(std::string query) const;
	void	exec(std::string query);

private:
	sqlite3 *_db = nullptr;
};
