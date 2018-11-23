#pragma once

#include <map>
#include <string>
#include <memory>

#include <boost/assign/list_inserter.hpp>
#include <boost/assign/list_of.hpp>

#include "sql_statement.h"
//#include "sql_type_converter.h"

#include "column_mapper.h"

namespace libORM
{
	/**
	* SQL Table mapper to C++ type
	*
	* @tparam T T is an object's type.
	* @tparam Id Id is the primary key's type.
	*/
	template<typename T, typename Id=int64_t>
	struct table_mapper
	{
		/**
		*  rowid type
		*/
		typedef Id rowid_type;
		
		/**
		 *  SQL table name
		 */
		//static const std::string table_name;
		static const std::string& table_name();

		/**
		 *  ROWID member
		 */
		static rowid_type T::* rowid()
		{
			return &T::ID;
		}

		/**
		 *  Create a new object
		 */
		static std::shared_ptr<T> new_object() {
			std::shared_ptr<T> t = std::make_shared<T>();
			(*t).*rowid() = 0;
			return t;
		};

		/**
		*  Parse from table
		*/
		static void from_datatable(int nCol, char** azVals, char** azCols, T & t);

		/**
		*  Write to table
		*/
		static void to_datatable(int nCol, char** azVals, char** azCols, const T & t);

		/**
		*  Default SQl SELECT statement
		*/
		static std::string select_sql()
		{
			sql_statement sql;
			sql << "SELECT * FROM " << table_name();
			return sql.str();
		}

		/**
		*  Default SQl SELECT statement
		*/
		static std::string select_sql(const rowid_type& id)
		{
			sql_statement sql;
			sql << "SELECT * FROM " << table_name() << " WHERE ID=" << id << ";";
			return sql.str();
		}

		/**
		*  Default SQl DELETE statement
		*/
		static std::string delete_sql(const rowid_type & id)
		{
			sql_statement sql;
			sql << "DELETE FROM " << table_name() << " WHERE ID=" << id << ";";
			return sql.str();
		}
		/**
		*  Default SQl DELETE statement
		*/
		static std::string delete_sql(const T & t)
		{
			return delete_sql(t.*rowid());
		}

		/**
		*  Default SQl INSERT statement
		*/
		static std::string insert_sql(const T& t)
		{
			sql_statement sql;
			std::map< std::string, std::string >  values = get_values(t);
			sql << "INSERT INTO " << table_name() << " " << format_insert_values(values) << ";";
			return sql.str();
		}


		/**
		*  Default SQl UPDATE statement
		*/
		static std::string update_sql(const T& t)
		{
			return update_sql(t,t.*rowid());
		}

		/**
		*  Default SQl UPDATE statement
		*/
		static std::string update_sql(const T& t, rowid_type id)
		{
			sql_statement sql;
			std::map< std::string, std::string >  values = get_values(t);
			sql << "UPDATE " << table_name() << " SET " << format_update_values(values)
				<< " WHERE ID=" << id;
			return sql.str();
		}

		/**
		*  Get object values
		*/
		static std::map<std::string, std::string> get_values(const T& t);

		/**
		*  Format values for an INSERT statement
		*/
		static std::string format_insert_values(const std::map<std::string, std::string>& values)
		{
			sql_statement sql;
			sql << "(";
			for (auto it = values.begin(); it != values.end(); )
			{
				sql << it->first;
				if (++it != values.end())
					sql << ",";
			}

			sql << ") VALUES (";
			for (auto it = values.begin(); it != values.end();)
			{
				sql << it->second;
				if (++it != values.end())
					sql << ",";
			}
			sql << ")";

			return sql.str();
		}

		/**
		*  Format values for an UPDATE statement
		*/
		static std::string format_update_values(const std::map<std::string, std::string>& values)
		{
			sql_statement sql;
			for (auto it = values.begin(); it != values.end(); )
			{
				sql << it->first << "=" << it->second;
				if (++it != values.end())
					sql << ",";
			}
			return sql.str();
		}

	
		//boost::fusion::set<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> columns;

	};

}
