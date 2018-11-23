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

		/**
		 * Construct a MSSQL implementation.
		 *
		 * @param a_szServer server name
		 * @param a_szDatabase database name
		*/
		explicit mssql_impl(const char* a_szServer, const char* a_szDatabase)
		: m_strServer(a_szServer)
		, m_strDatabase(a_szDatabase)
		{};

		/**
		 * Construct a MSSQL implementation.
		 *
		 * @param a_strServer server name
		 * @param a_strDatabase database name
		*/
		explicit mssql_impl(const std::string& a_strServer, const std::string& a_strDatabase)
			: m_strServer(a_strServer)
			, m_strDatabase(a_strDatabase)
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
		virtual int64_t LastInsertRowId() {
			throw std::logic_error("Function not yet implemented.");
		}
	private:
		std::string m_strServer;
		std::string m_strDatabase;
	};

}
