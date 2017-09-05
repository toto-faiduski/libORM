#pragma once

#include <ctime>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>

#include "table_mapper.h"

namespace libORM
{

	/**
	* SQL DateTime type
	*/
	class sql_date_time
	{
	public:
		//! Construct a sql_date_time
		/*!
		\param a_t time
		*/
		sql_date_time(const std::time_t & a_t):m_t(a_t){}

		//! Return embedded time
		operator std::time_t() const{
			return m_t;
		}
	private:
		std::time_t m_t;
	};


	/**
	* Converter for various types
	*/
	struct sql_type_converter
	{
		template<typename T>
		static std::string to_sql(const T & t)
		{
			std::ostringstream ss;
			ss << t;
			return ss.str();
		}

		template<typename T>
		static std::string to_sql(const std::shared_ptr<T>& t)
		{
			std::ostringstream ss;
			if(!t)
				ss << "NULL";
			else
				ss << to_sql( table_mapper<T>::get_rowid(*t.get()));
			return ss.str();
		};

		//template<>
		static std::string to_sql(const std::string & t)
		{
			std::ostringstream ss;
			ss << "'" << t << "'";
			return ss.str();
		};

		//template<>
		//static std::string to_sql<sql_date_time>(const sql_date_time & a_t)
		//{
		//	const time_t tt = a_t;
		//	struct tm t = { 0 };
		//	gmtime_s(&t, &tt);
		//	char szDate[512];
		//	strftime(szDate, 512, "'%Y-%m-%d %H:%M:%S'", &t);
		//	return std::string(szDate);
		//};

		template<typename T>
		static std::string to_sql(const boost::optional<T> & t)
		{
			if (t)
				return to_sql(*t);
			else
				return "NULL";
		}

		//template<>
		//static std::string to_sql(const std::time_t & a_t)
		static std::string to_sql_time(const std::time_t & a_t)
		{
			struct tm t = { 0 };
			gmtime_s(&t, &a_t);
			char szDate[512];
			strftime(szDate, 512, "'%Y-%m-%d %H:%M:%S'", &t);
			return std::string(szDate);
		};

		static std::string to_sql_time(const boost::optional<std::time_t> & t)
		{
			if (t)
				return to_sql_time(*t);
			else
				return "NULL";
		}

		// Generic member
		template<typename T>
		static void from_sql(T & t, const char* value)
		{
			if (value != nullptr)
				t = boost::lexical_cast<T>(value);
		}

		// Generic optional member
		template<typename T>
		static void from_sql(boost::optional<T> & a_t, const char* value)
		{
			if (value == nullptr)
				return;
			T t;
			from_sql(t, value);
			a_t = t;
		}

		// DateTime member
		//template<>
		//static void from_sql(time_t & a_t, const char* value)
		static void from_sql_time(time_t & a_t, const char* value)
		{
			if (value == nullptr)
				return;
			struct tm t = { 0 };
			sscanf_s(value, "%04d-%02d-%02d %02d:%02d:%02d", &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec);
			t.tm_year -= 1900;
			t.tm_mon--;
			a_t = _mkgmtime(&t);
		}

		static void from_sql_time(boost::optional<time_t> & a_t, const char* value)
		{
			if (value == nullptr)
				return;
			time_t t;
			from_sql_time(t, value);
			a_t = t;
		}

		// Complex member
		template<typename T>
		static void from_sql(std::shared_ptr<T> & t, const char* value)
		{
			if (value == nullptr)
				return;
			if (t == nullptr) t = std::make_shared<T>();
			from_sql(t->ID, value);
		}
	};

}
