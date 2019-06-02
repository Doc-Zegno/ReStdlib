#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <cstring>


#include "Any.h"


namespace ReLang {
	namespace Utils {
		Ptr<String> makeStringFromBuilder(const std::wostringstream& builder);


		// TODO: remove this
		/*template<typename T>
		void appendToBuilder(std::wostringstream& builder, T value) {
			builder << value;
		}*/


		void appendToBuilder(std::wostringstream& builder, Ptr<String> value);


		template<typename T>
		void appendToBuilder(std::wostringstream& builder, T value) {
			appendToBuilder(builder, toString(value));
		}


		// TODO: remove this
		/*void appendToBuilder(std::wostringstream& builder, Ptr<Any> value);


		template<typename T>
		void appendToBuilder(std::wostringstream& builder, Ptr<T> value) {
			auto any = staticPointerCast<Any>(value);
			appendToBuilder(builder, any);
		}*/
	}
}
