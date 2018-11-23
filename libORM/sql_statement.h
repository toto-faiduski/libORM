#pragma once

#include <sstream>
#include <list>
//#include <numeric>

#include <iomanip>

namespace libORM
{
	/**
	* Statement for a SQL request
	*/
	class sql_statement : public std::ostringstream
	{
	public:
		/**
		* Statement default contructor
		*/
		sql_statement() {}

		/**
		* Statement contructor from string
		*/
		explicit sql_statement(const std::basic_string<char>& _Str) : std::ostringstream(_Str) {}
	};



	//std::_Smanip<int>	__cdecl param(int no);
	//std::_Smanip<const std::string&>	__cdecl param(const std::string& no);


	/**
	* Statement container for a SQL request
	*/
	class sql_statement_list
	{
	public:
		/**
		* Default contructor
		*/
		sql_statement_list() {
		}

		/**
		* Contructor from Statement
		*/
		explicit sql_statement_list(const sql_statement& sql_stmt) : m_str(sql_stmt.str()){
		}

		/**
		* Add a string Statement
		*/
		void add(const std::string& sql_stmt) {
			m_str << sql_stmt << std::endl;
		}

		/**
		* Add a sql_statement Statement
		*/
		void add(const sql_statement& sql_stmt) {
			m_str << sql_stmt.str() << std::endl;
		}

		/**
		* Get the statement string
		*/
		std::string str() {
			return m_str.str();
		}

	private:
		std::ostringstream m_str;
	};
}
