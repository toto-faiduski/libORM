#include "sqlite_impl.h"

#include <sstream>


namespace libORM
{

	/**********************************************/
	//! Construct a SQLITE implementation.
	/*!
	\param a_szDatabasePath Path to the database file
	*/
	/**********************************************/
	sqlite_impl::sqlite_impl(const char* a_szDatabasePath)
		: m_pDb(NULL)
		, m_szDatabasePath(a_szDatabasePath)
	{
	}

	/**********************************************/
	//! sqlite_impl destructor.
	/**********************************************/
	sqlite_impl::~sqlite_impl()
	{
		if (m_pDb) {
			try {
				Close();
			}
			catch (...) {

			}
		}
	}

	/**********************************************
	//! Open the database
	***********************************************/
	void sqlite_impl::Open()
	{
		if (m_pDb != NULL)
			Close();

		int i = sqlite3_open(m_szDatabasePath.c_str(), &m_pDb);
		SQLITE_ASSERT(i);
	}

	/**********************************************
	* Close the database
	***********************************************/
	void sqlite_impl::Close()
	{
		if (m_pDb == NULL)
			return ;
		int i = sqlite3_close(m_pDb);
		SQLITE_ASSERT(i);
		m_pDb = NULL;
	}

	/**********************************************/
	//! Execute a SQL statement
	/*!
	\param sql sql statement
	\param callback sql statement
	\param p sql statement
	\param errmsg sql statement
	*/
	/**********************************************/
	int sqlite_impl::ExecuteSQL(
		const char *sql,										/* SQL to be evaluated */
		int(*callback)(void*, int, char**, char**),	/* Callback function */
		void *p,													/* 1st argument to callback */
		char **errmsg)											/* Error msg written here */
	{
		if (m_pDb)
		{
			int i = sqlite3_exec(m_pDb, sql, callback, p, errmsg);
			SQLITE_EXEC_ASSERT(i, *errmsg);
			return i;
		}
		throw std::runtime_error("database not opened");
	}

	/**********************************************
	* Return the ROWID of the most recent insert
	***********************************************/
	__int64 sqlite_impl::LastInsertRowId() 
	{
		if (m_pDb)
		{
			return sqlite3_last_insert_rowid(m_pDb);
		}
		throw std::runtime_error("database not opened");
	}

}