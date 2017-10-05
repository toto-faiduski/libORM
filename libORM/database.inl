//
// database class implementation
//
#include "implementation.h"
#include "table_mapper.h"

namespace libORM
{

	/**
	 * @brief Generic callback for sql request.
	 *
	 * @tparam T the type of object to get
	 * @param pArg the object to receive the unique record
	 * @param nCol the number of columns in the result
	 * @param azVals an array of pointers to strings, one for each column, where each entry represents the value of corresponding result column
	 * @param azCols an array of pointers to strings, one for each column, where each entry represents the name of corresponding result column
	*/
	template<class T>
	int database::callback_Get(void* pArg, int nCol, char** azVals, char** azCols)
	{
		std::shared_ptr<T>* pptr = static_cast<std::shared_ptr<T>*>(pArg);
		if (pptr->get()==nullptr)
			(*pptr) = std::make_shared<T>();
		table_mapper<T>::from_datatable(nCol, azVals, azCols, *(*pptr).get());
		return 0;
	}

	/**
	 * @brief Generic callback for sql request.
	 * 
	 * @tparam _Container the type of object container to get
	 * @param pList the container to receive records
	 * @param nCol the number of columns in the result
	 * @param azVals an array of pointers to strings, one for each column, where each entry represents the value of corresponding result column
	 * @param azCols an array of pointers to strings, one for each column, where each entry represents the name of corresponding result column
	*/
	template<class _Container>
	int database::callback_GetAll(void* pList, int nCol, char** azVals, char** azCols)
	{
		auto elem = std::make_shared<_Container::value_type::_Elem>();
		table_mapper< typename _Container::value_type::_Elem >::from_datatable(nCol, azVals, azCols, *elem);

		back_inserter(*(static_cast<_Container*>(pList))) = elem;
		return 0;
	}

	/**
	 * @brief Get all/many records from a database table.
	 * 
	 * @tparam _Container the type of object container to get
	 * @param l the container to receive records
	 * @param szSQL an optional sql statement
	*/
	template<class _Container>
	void database::Get(_Container& l, const char* szSQL /*= NULL*/)
	{
		int i;
		char* errmsg = NULL;

		l.clear();

		// Execute SELECT statement
		if (szSQL == NULL)
			i = pimpl_->ExecuteSQL( table_mapper< typename _Container::value_type::_Elem >::select_sql().c_str(), &database::callback_GetAll<_Container>, &l, &errmsg);
		else
			i = pimpl_->ExecuteSQL( szSQL, &database::callback_GetAll<_Container>, &l, &errmsg);
	}

	/**
	 * @brief Get an object from a database table.
	 * 
	 * @tparam T the type of object to get
	 * @param id row_id of the record to retreive
	 * @param pt the record
	*/
	template<class T>
	void database::Get(int64_t id, std::shared_ptr<T>& pt)
	{
		int i;
		char* errmsg = NULL;

		// Execute UPDATE statement
		i = pimpl_->ExecuteSQL( table_mapper<T>::select_sql(id).c_str(), &database::callback_Get<T>, &pt, &errmsg);
	}

	/**
	 * @brief Insert an Object into database.
	 *
	 * @tparam T the type of object to insert
	 * @param t the object
	*/
	template<class T>
	void database::Insert(T& t)
	{
		int i;
		char* errmsg = NULL;

		// Execute INSERT statement
		i = pimpl_->ExecuteSQL( table_mapper<T>::insert_sql(t).c_str(), NULL, NULL, &errmsg);

		// Get inserted ID
		int64_t id = pimpl_->LastInsertRowId();
		table_mapper<T>::set_rowid(t, id);
	}

	/**
	 * @brief Update an Object into database.
	 *
	 * @tparam T the type of object to update
	 * @param t the object
	*/
	template<class T>
	void database::Update(T& t)
	{
		//int i;
		//char* errmsg = NULL;

		// Execute UPDATE statement
		//i = pimpl_->ExecuteSQL( table_mapper<T>::update_sql(t).c_str(), NULL, NULL, &errmsg);
		Update(t, table_mapper<T>::get_rowid(t));
	}

	/**
	 * @brief Update an Object into database.
	 * 
	 * @tparam T the type of object to update
	 * @param t the object
	 * @param id row_id of the object
	*/
	template<class T>
	void database::Update(T& t, int64_t id)
	{
		int i;
		char* errmsg = NULL;

		// Execute UPDATE statement
		i = pimpl_->ExecuteSQL( table_mapper<T>::update_sql(t, id).c_str(), NULL, NULL, &errmsg);
	}

	/**
	 * @brief Remove an Object from database.
	 *
	 * @tparam T the type of object to remove
	 * @param t the object
	*/
	template<class T>
	void database::Remove(T& t)
	{
		int i;
		char* errmsg = NULL;

		//sql_statement sql;
		//sql << "BEGIN TRANSACTION;" << std::endl;
		//sql << table_mapper<T>::delete_sql(t) << std::endl;
		//sql << "COMMIT TRANSACTION;" << std::endl;


		sql_statement_list sql;
		//sql.add( sql_statement("BEGIN TRANSACTION") );
		sql.add("BEGIN TRANSACTION;");

		sql.add(table_mapper<T>::delete_sql(t));

		sql.add("COMMIT TRANSACTION;");


		// Execute DELETE statement
		i = pimpl_->ExecuteSQL(sql.str().c_str(), NULL, NULL, &errmsg);
		//i = pimpl_->ExecuteSQL( table_mapper<T>::delete_sql(t).c_str(), NULL, NULL, &errmsg);
	}

}
