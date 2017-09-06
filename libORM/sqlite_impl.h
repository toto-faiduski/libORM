#pragma once

#include "database.h"
#include "implementation.h"

#include "sqlite3.h"
#include <string>

namespace libORM
{
	/**
	* Construct a SQLite implementation.
	*
	* \param a_szDatabasePath Path to the database file
	*/
	class sqlite_impl : public implementation
	{
		public:
			explicit sqlite_impl(const char* a_szDatabasePath);
			~sqlite_impl();

			virtual void Open();
			virtual void Close();

			virtual int ExecuteSQL( const char *sql, int(*callback)(void*, int, char**, char**), void *p, char **errmsg);
			virtual int64_t LastInsertRowId();

	private:
			sqlite3 *m_pDb;
			std::string m_szDatabasePath;

			template<typename T>
			inline void SQLITE_ASSERT(const T& i)
			{
				if (i != SQLITE_OK) {
					std::ostringstream ss;
					ss << "sqlite error " << sqlite3_errcode(m_pDb);
					ss << " : " << sqlite3_errmsg(m_pDb);
					/*DebugBreak();*/
					throw std::runtime_error(ss.str());
				}
			}

			template<typename T, typename U>
			inline void SQLITE_EXEC_ASSERT(const T& i, const U& errmsg)
			{
				if (i != SQLITE_OK) {
					std::ostringstream ss;
					ss << "sqlite error " << i;
					if (errmsg) {
						/*DebugBreak();*/
						ss << " : " << errmsg;
						sqlite3_free(errmsg);
					}
					throw std::runtime_error(ss.str());
				}
			}
	};

}
