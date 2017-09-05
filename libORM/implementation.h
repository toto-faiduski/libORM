#pragma once

namespace libORM
{

	/*! \brief brief description.
	*
	* A base class for all kind of SQL implementations.
	*/
	class implementation {
	public:
		virtual ~implementation() {};

		/**
		* Open the database
		*/
		virtual void Open() = 0;

		/**
		* Close the database
		*/
		virtual void Close() = 0;

		/**
		* Execute the SQL statement
		*/
		virtual int ExecuteSQL(const char *sql, int(*callback)(void*, int, char**, char**), void *p, char **errmsg) = 0;

		/**
		* Get the last inserted rowid
		*/
		virtual int64_t LastInsertRowId() = 0;
	};



}
