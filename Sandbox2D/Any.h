#pragma once
#include <string>

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

			if (typeHolderPtr->_typeName != typeid(T).name())
			{
				std::cout << "Warning! Casting from " << typeHolderPtr->_typeName.c_str() << " to " << typeid(T).name() << " might be unsafe." << std::endl;
			}

			auto* dhPtr = static_cast<DataHolder<T>*>(typeHolderPtr);

			DataHolder<T> dh = *dhPtr;

			return dh._data;
		}

		template<typename T>
		void free() const
		{
			const auto typeHolderPtr = _typeHolder;

			auto* dhPtr = static_cast<DataHolder<T>*>(typeHolderPtr);

			delete dhPtr;
		}
	};
}