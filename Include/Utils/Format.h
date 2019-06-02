#pragma once

#include "Utils/Builder.h"


namespace ReLang {
	namespace Utils {
		template<typename T>
		void formatToBuilder(std::wostringstream& builder, T arg) {
			appendToBuilder(builder, arg);
		}


		template<typename T, typename ...TArgs>
		void formatToBuilder(std::wostringstream& builder, T arg, TArgs ...rest) {
			appendToBuilder(builder, arg);
			formatToBuilder(builder, rest...);
		}


		template<typename T, typename ...TArgs>
		Ptr<String> format(T first, TArgs ...rest) {
			auto builder = std::wostringstream();
			formatToBuilder(builder, first, rest...);
			return makeStringFromBuilder(builder);
		}
	}
}
