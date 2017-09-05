#include "database.h"
#include "sqlite_impl.h"
#include "mssql_impl.h"
#include "sql_statement.h"

namespace libORM
{
	/**
	* Private construction
	*/
	database::database(implementation* impl)
		: pimpl_(impl)
	{
	}

   //! A factory function for a SQLite database.
	/*!
		\param a_saDatabasePath database file path
		\return a database object
	*/
	std::shared_ptr<database> database::CreateSQLiteDatabase(const char *a_saDatabasePath)
	{
		return std::shared_ptr<database>(new database(new sqlite_impl(a_saDatabasePath)));
	}

   //! A factory function for a MSSQL Server database.
	/*!
		\param a_Server server name
		\param a_Database database name
		\return a database object
	*/
	std::shared_ptr<database> database::CreateMSSQLDatabase(const char *a_Server, const char *a_Database)
	{
		return std::shared_ptr<database>(new database(new mssql_impl(a_Server, a_Database)));
	}

	//! Open the database.
	void database::Open()
	{
		pimpl_->Open();
	}

	//! Close the database.
	void database::Close()
	{
		pimpl_->Close();
	}

	//! Execute a SQL statement.
	/*!
	\param sql SQL statement
	\param callback callback
	\param p private data
	\param errmsg error message
	\return error code
	*/
	int database::ExecuteSQL(const char *sql, int(*callback)(void*, int, char**, char**), void *p, char **errmsg)
	{
		return pimpl_->ExecuteSQL(sql,callback,p,errmsg);
	}

	//! Begin a SQL transaction.
	/*!
	*/
	void database::BeginTransaction()
	{
		int i;
		char* errmsg = NULL;

		// Execute statement
		i = pimpl_->ExecuteSQL("BEGIN TRANSACTION", NULL, NULL, &errmsg);
	}

	//! Commit a SQL transaction.
	/*!
	*/
	void database::CommitTransaction()
	{
		int i;
		char* errmsg = NULL;

		// Execute statement
		i = pimpl_->ExecuteSQL("COMMIT TRANSACTION", NULL, NULL, &errmsg);
	}

	//! Rollback a SQL transaction.
	/*!
	*/
	void database::RollbackTransaction()
	{
		int i;
		char* errmsg = NULL;

		// Execute statement
		i = pimpl_->ExecuteSQL("ROLLBACK TRANSACTION", NULL, NULL, &errmsg);
	}


/*
	void fb(std::ios_base& os, int l)
	{
		std::ostream *pos = dynamic_cast<std::ostream*>(&os);
		if (pos)
		{
			//for (int i = 0; i < l; i++)
			//	(*pos) << ' ';
			(*pos) << "'" << l << "'";
		};
	}

	std::_Smanip<int>
		__cdecl param(int no)
	{
		return (std::_Smanip<int>(&fb, no));
	}




	void fb(std::ios_base& os, const std::string& no)
	{
		std::ostream *pos = dynamic_cast<std::ostream*>(&os);
		if (pos)
		{
			//for (int i = 0; i < l; i++)
			//	(*pos) << ' ';
			(*pos) << "'" << no << "'";
		};
	}

	std::_Smanip<const std::string&>
		__cdecl param(const std::string& no)
	{
		return (std::_Smanip<const std::string&>(&fb, no));
	}
*/
}
