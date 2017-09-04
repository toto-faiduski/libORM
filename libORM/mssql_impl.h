#pragma once

#include "database.h"
#include "implementation.h"

#include <string>

namespace libORM
{
	/**
	* A MSSQL Server implemantation of SQL
	*/
	class mssql_impl : public implementation
	{
	public:

		//! Construct a MSSQL implementation.
		/*!
		\param a_szServer server name
		\param a_szDatabase database name
		*/
		explicit mssql_impl(const char* a_szServer, const char* a_szDatabase)
		: m_szServer(a_szServer)
		, m_szDatabase(a_szDatabase)
		{};

		virtual void Open() {
			throw std::logic_error("Function not yet implemented.");
		}
		virtual void Close() {
			throw std::logic_error("Function not yet implemented.");
		}

		virtual int ExecuteSQL(const char *sql, int(*callback)(void*, int, char**, char**), void *p, char **errmsg) {
			throw std::logic_error("Function not yet implemented.");
		}
		virtual __int64 LastInsertRowId() {
			throw std::logic_error("Function not yet implemented.");
		}
	private:
		std::string m_szServer;
		std::string m_szDatabase;
	};

}
