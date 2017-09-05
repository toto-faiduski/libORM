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
		sql_statement() {}
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
		sql_statement_list() {
		}

		explicit sql_statement_list(const sql_statement& sql_stmt) : m_str(sql_stmt.str()){
		}

		void add(const std::string& sql_stmt) {
			m_str << sql_stmt << std::endl;
		}

		void add(const sql_statement& sql_stmt) {
			m_str << sql_stmt.str() << std::endl;
		}

		std::string str() {
			return m_str.str();
		}

	private:
		std::ostringstream m_str;
	};
}
