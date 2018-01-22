// Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <typeinfo>  
#include <vector>
#include <algorithm>
#include <functional>


//struct Any
//{
//	struct TypeHolder
//	{
//		std::string type_name;
//	};
//
//	template<typename T>
//	struct DataHolder : TypeHolder
//	{
//		T data;
//	};
//	
//	TypeHolder* type_holder;
//	
//	template<typename T>
//	Any(T data)
//	{
//		Any::DataHolder<T>* data_holder = new Any::DataHolder<T>;
//
//		data_holder->data = data;
//		data_holder->type_name = std::string(typeid(data).raw_name());
//
//		this->type_holder = static_cast<Any::TypeHolder*>(data_holder);
//	}
//
//	Any()
//	{
//		this->assign(0);
//	}
//	template<typename T>
//	Any assign(T data)
//	{
//		Any::DataHolder<T>* data_holder = new Any::DataHolder<T>;
//
//		data_holder->data = data;
//		data_holder->type_name = std::string(typeid(data).raw_name());
//
//		this->type_holder = static_cast<Any::TypeHolder*>(data_holder);
//
//		return *this;
//	};
//
//	template <class T>
//	Any operator=(T data) {
//		return assign(data);
//	};
//
//};
//
//template<typename T>
//T any_cast(Any any)
//{
//	if ( any.type_holder->type_name != typeid(T).raw_name())
//	{
//		std::cout << "Unsafe casting of Any, please beware (" << any.type_holder->type_name.c_str() << " to " << typeid(T).raw_name() << ")" << std::endl;
//	}
//	Any::DataHolder<T>* dh_ptr = (Any::DataHolder<T>*) any.type_holder;
//	return dh_ptr->data;
//}

struct Mouse
{
	int X; 
	int Y;
	bool isDown;
};

template<typename T, typename ACC>
ACC reduce(std::function<ACC(ACC, T)> fn, std::vector<T> list, ACC acc)
{
	ACC accumulator = acc;

	for ( size_t i = 0; i < list.size(); i++ )
	{
		accumulator = fn(accumulator, list[i]);
	}

	return accumulator;
}

template<typename T>
std::vector<T> map(std::function<T(T)> fn, std::vector<T> list)
{
	std::vector<T> nlist;

	for ( T elem : list )
	{
		nlist.push_back(fn(elem));
	}

	return nlist;
}

std::vector<int> range(int min, int max)
{
	std::vector<int> rng;
	for (int i = min; i <= max; i++) rng.push_back(i);

	return rng;
}

namespace Any
{
	struct TypeHolder
	{
		std::string _typeName;
	};

	template<typename T>
	struct DataHolder : TypeHolder
	{
		T _data{};
	};

	struct Any
	{
		TypeHolder* _typeHolder = nullptr;

		template<typename T>
		explicit Any(T data)
		{
			auto* dhPtr = new DataHolder<T>;

			dhPtr->_data = data;
			dhPtr->_typeName = std::string(typeid(data).name());

			_typeHolder = static_cast<TypeHolder*>(dhPtr);
		}

		template<typename T>
		T castTo()
		{
			const auto typeHolderPtr = _typeHolder;

			if ( typeHolderPtr->_typeName != typeid(T).name() )
			{
				std::cout << "Warning! Casting from " << typeHolderPtr->_typeName.c_str() << " to " << typeid(T).name() << " might be unsafe." << std::endl;
			}

			auto* dhPtr = static_cast<DataHolder<T>*>(typeHolderPtr);

			DataHolder<T> dh = *dhPtr;

			return dh._data;
		}

		template<typename T>
		void free()
		{
			const auto typeHolderPtr = _typeHolder;

			auto* dhPtr = static_cast<DataHolder<T>*>(typeHolderPtr);

			delete dhPtr;
		}
	};
}

int main()
{

	system("pause");

	return 0;
}
