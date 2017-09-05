#pragma once

#include <map>
#include <string>

#include <boost/config/suffix.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/assign/list_of.hpp>

#include "sql_statement.h"
//#include "sql_type_converter.h"

namespace libORM
{
	/**
	* SQL Table mapper to C++ type
	*/
	template<typename T>
	struct table_mapper
	{


		/**
		*  Tous les mappages champs-valeurs associés a une requete
		*/
		/*class Values : public std::map<std::string, std::string>
		{
		private:
			typedef std::map<std::string, std::string>  values_map;

			class add_to_map
			{
				std::map<std::string, std::string>& c_;
			public:

				add_to_map(values_map& c) : c_(c)
				{ }

				template<class U>
				void operator()(const std::string& key, const U& val)
				{
					c_.insert(std::make_pair(key, sql_type_converter::to_sql(val)));
				}
			};

		public:

			template<class U>
			boost::assign::list_inserter< add_to_map > add(std::string key, const U& val)
			{
				return boost::assign::make_list_inserter(add_to_map(*this))(key, val);
			}
		};*/

		/*
		*  SQL table name
		*/
		static const std::string table_name;

		/*
		*  Set ROWID
		*/
		static void set_rowid(T & t,int64_t id)
		{
			t.ID = id;
		}

		/*
		*  Get ROWID
		*/
		static int64_t get_rowid(const T & t)
		{
			return t.ID;
		}

		/*
		*  Create a new object
		*/
		static std::shared_ptr<T> new_object() {
			std::shared_ptr<T> t = std::make_shared<T>();
			set_rowid(*t.get(), 0);
			return t;
		};

		/*
		*  Parse from table
		*/
		static void from_datatable(int nCol, char** azVals, char** azCols, T & t);

		/*
		*  Write to table
		*/
		static void to_datatable(int nCol, char** azVals, char** azCols, const T & t);

		/*
		*  Default SQl SELECT statement
		*/
		static std::string select_sql()
		{
			sql_statement sql;
			sql << "SELECT * FROM " << table_name;
			return sql.str();
		}

		/*
		*  Default SQl SELECT statement
		*/
		static std::string select_sql(int64_t id)
		{
			sql_statement sql;
			sql << "SELECT * FROM " << table_name << " WHERE ID=" << id << ";";
			return sql.str();
		}

		/*
		*  Default SQl DELETE statement
		*/
		static std::string delete_sql(const T & t)
		{
			sql_statement sql;
			sql << "DELETE FROM " << table_name << " WHERE ID=" << get_rowid(t) << ";";
			return sql.str();
		}

		/*
		*  Default SQl INSERT statement
		*/
		static std::string insert_sql(const T& t)
		{
			sql_statement sql;
			std::map< std::string, std::string >  values = get_values(t);
			sql << "INSERT INTO " << table_name << " " << format_insert_values(values) << ";";
			return sql.str();
		}


		/*
		*  Default SQl UPDATE statement
		*/
		static std::string update_sql(const T& t)
		{
			return update_sql(t,get_rowid(t));
		}

		static std::string update_sql(const T& t, int64_t id)
		{
			sql_statement sql;
			std::map< std::string, std::string >  values = get_values(t);
			sql << "UPDATE " << table_name << " SET " << format_update_values(values)
				<< " WHERE ID=" << id;
			return sql.str();
		}

		//typedef std::map<std::string, std::string> map_values;



		/*
		*  Get object values
		*/
		static std::map<std::string, std::string> get_values(const T& t);

		/*
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

		/*
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
	};


	//template< class T >
	//inline boost::assign_detail::generic_list< std::pair
	//	<
	//	BOOST_DEDUCED_TYPENAME boost::assign_detail::assign_decay<std::string>::type,
	//	BOOST_DEDUCED_TYPENAME boost::assign_detail::assign_decay<std::string>::type
	//> >
	//	values_list_of(const std::string& k, const T& t)
	//{
	//	typedef BOOST_DEDUCED_TYPENAME boost::assign_detail::assign_decay<std::string>::type k_type;
	//	typedef BOOST_DEDUCED_TYPENAME boost::assign_detail::assign_decay<T>::type   t_type;
	//	return boost::assign_detail::generic_list< std::pair<k_type, k_type> >()(k, sql_type_converter::to_sql(t));
	//}

}
