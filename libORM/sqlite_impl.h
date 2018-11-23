#pragma once

#include "database.h"
#include "implementation.h"

#include "sqlite3.h"
#include <string>

namespace libORM
{
	/**
	* A SQLite implemantation of SQL
	*/
	class sqlite_impl : public implementation
	{
		public:
			/**
			* Construct a SQLite implementation.
			*
			* @param a_szDatabasePath Path to the database file
			*/
			explicit sqlite_impl(const char* a_szDatabasePath);

			/**
			* Construct a SQLite implementation.
			*
			* @param a_strDatabasePath Path to the database file
			*/
			explicit sqlite_impl(const std::string& a_strDatabasePath);

			~sqlite_impl();

			virtual void Open();
			virtual void Close();

			virtual int ExecuteSQL( const char *sql, int(*callback)(void*, int, char**, char**), void *p, char **errmsg);
			virtual int64_t LastInsertRowId();

	private:
			sqlite3 *m_pDb;
			std::string m_strDatabasePath;

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
