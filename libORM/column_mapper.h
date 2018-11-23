#pragma once

#include <string>

namespace libORM
{
	template<class O, class T>
	class column_mapper
	{
	public:
		typedef O object_type;
		typedef T field_type;
		typedef field_type object_type::*member_pointer_t;
		typedef const field_type& (object_type::*getter_type)() const;
		typedef void (object_type::*setter_type)(field_type);

		/**
		*  Column name.
		*/
		const std::string name;

		/**
		*  Member pointer used to read/write member
		*/
		member_pointer_t member_pointer/* = nullptr*/;

		/**
		*  Getter member function pointer to get a value. If member_pointer is null then
		*  `getter` and `setter` must be not null
		*/
		getter_type getter/* = nullptr*/;

		/**
		*  Setter member function pointer to set a value.
		*/
		setter_type setter/* = nullptr*/;

	};

}
#pragma once
