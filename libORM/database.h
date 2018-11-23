#pragma once

#include <memory>
#include <cstdint>
#include <string>

namespace libORM
{
	class implementation;

	/**
	* The database access class
	*/
	class database {
		explicit database(implementation* impl);

	public:

		// A factory function for a SQLite database
		static std::shared_ptr<database> CreateSQLiteDatabase(const char *a_DatabasePath);
		static std::shared_ptr<database> CreateSQLiteDatabase(const std::string& a_strDatabasePath);

		// A factory function for a MSSQL Server database
		static std::shared_ptr<database> CreateMSSQLDatabase(const char *a_Server, const char *a_Database);
		static std::shared_ptr<database> CreateMSSQLDatabase(const std::string& a_Server, const std::string& a_Database);

		// Open the database
		void Open();

		// Close the database
		void Close();

		int ExecuteSQL(const char *sql, int(*callback)(void*, int, char**, char**), void *p, char **errmsg);

		template<class _Container>
		void Get(_Container& t, const char* szSQL = NULL);

		template<class T, class Id>
		void Get(Id id, std::shared_ptr<T>& pt);

		template<class T>
		void Insert(T& t);

		template<class T>
		void Update(T& t);

		template<class T, class Id>
		void Update(T& t, Id id);

		template<class T, class Id>
		void Remove(Id id);
		template<class T>
		void Remove(T& t);
		template<class T>
		void Remove(std::shared_ptr<T>& t);

		void BeginTransaction();
		void CommitTransaction();
		void RollbackTransaction();

	protected:

		template<class _Container>
		static int callback_GetAll(void*, int, char**, char**);

		template<class T>
		static int callback_Get(void*, int, char**, char**);

	private:
		// Use PIMPL idiom to hide implementation
		std::unique_ptr<implementation> pimpl_;
	};

}

#include "database.inl"
