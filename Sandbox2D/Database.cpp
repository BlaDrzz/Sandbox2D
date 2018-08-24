#include "../stdafx.h"

#include "Database.h"

Database::Database(const std::string filename)
{
	sqlite3_open(filename.c_str(), &_db);
}

Database::~Database()
{
	sqlite3_close(_db);
}

Table Database::fetchAll(const std::string query) const
{
	Table tbl;
	char *errMsg = nullptr;

	sqlite3_exec(_db, query.c_str(), [](void *data, int colCount, char **colValue, char **colName)
	{
		Row row;

		for (auto i = 0; i < colCount; i++)
		{
			row[colName[i]] = colValue[i] ? std::string(colValue[i]) : "NULL";
		}

		static_cast<Table*>(data)->push_back(row);

		return 0;
	}, &tbl, &errMsg);

	return tbl;
}