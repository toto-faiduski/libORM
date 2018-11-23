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
		@param a_t time
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
		/**
		* Default converter
		*/
		template<typename T>
		static std::string to_sql(const T & t)
		{
			std::ostringstream ss;
			ss << t;
			return ss.str();
		}

		/**
		* String converter
		*/
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

		/**
		* Generic optional value converter
		*/
		template<typename T>
		static std::string to_sql(const boost::optional<T> & t)
		{
			if (t)
				return to_sql(*t);
			else
				return "NULL";
		}

		/**
		* Generic optional value converter
		*/
		template<typename T>
		static std::string to_sql(const std::shared_ptr<T>& t)
		{
			if (t)
				return to_sql(*t);
			else
				return "NULL";
		};

		/**
		* Unix date converter
		*/
		static std::string to_sql_datetime(const std::time_t & a_t)
		{
			std::ostringstream ss;
			ss << "datetime(" << a_t << ",'unixepoch')";
			return ss.str();

			//struct tm t = { 0 };
			//gmtime_s(&t, &a_t);
			//char szDate[512];
			//strftime(szDate, 512, "'%Y-%m-%d %H:%M:%S'", &t);
			//return std::string(szDate);
		};

		/**
		* Julian date converter
		*/
		static std::string to_sql_datetime(const double& a_t)
		{
			std::ostringstream ss;
			ss << "datetime(" << a_t << ")";
			return ss.str();
		}
		
		/**
		* Optional date converter
		*/
		template< typename T>
		static std::string to_sql_datetime(const boost::optional<T> & t)
		{
			if (t)
				return to_sql_datetime(*t);
			else
				return "NULL";
		}
		
		/**
		* Optional date converter
		*/
		template< typename T>
		static std::string to_sql_datetime(const std::shared_ptr<T> & t)
		{
			if (t)
				return to_sql_datetime(*t);
			else
				return "NULL";
		}

		/**
		* Default converter
		*/
		template<typename T>
		static void from_sql(T & t, const char* value)
		{
			if (value != nullptr)
				t = boost::lexical_cast<T>(value);
		}

		/**
		* Generic optional value converter
		*/
		template<typename T>
		static void from_sql(boost::optional<T> & a_t, const char* value)
		{
			if (value == nullptr)
				return;
			T t;
			from_sql(t, value);
			a_t = t;
		}

		/**
		* Generic optional value converter
		*/
		template<typename T>
		static void from_sql(std::shared_ptr<T> & a_t, const char* value)
		{
			if (value == nullptr)
				return;
			T t;
			from_sql(t, value);
			a_t = std::make_shared<T>(t);
		}

		/**
		* Unix date converter
		*/
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

		/**
		* Optional Unix date converter
		*/
		static void from_sql_time(boost::optional<time_t> & a_t, const char* value)
		{
			if (value == nullptr)
				return;
			time_t t;
			from_sql_time(t, value);
			a_t = t;
		}

		/**
		* Optional Unix date converter
		*/
		static void from_sql_time(std::shared_ptr<time_t> & a_t, const char* value)
		{
			if (value == nullptr)
				return;
			time_t t;
			from_sql_time(t, value);
			a_t = std::make_shared<time_t>(t);
		}

		// Complex member
		//template<typename T>
		//static void from_sql(std::shared_ptr<T> & t, const char* value)
		//{
		//	if (value == nullptr)
		//		return;
		//	if (t == nullptr) t = std::make_shared<T>();
		//	from_sql(t->ID, value);
		//}
	};

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

			!!! ne marche pas pour les time_t !!!
			template<>
			void operator()(const std::string& key, const time_t& val)
			{
				c_.insert(std::make_pair(key, sql_type_converter::to_sql_datetime(val)));
			}
		};

	public:

		template<class U>
		boost::assign::list_inserter< add_to_map > add(std::string key, const U& val)
		{
			return boost::assign::make_list_inserter(add_to_map(*this))(key, val);
		}
	};*/

}
