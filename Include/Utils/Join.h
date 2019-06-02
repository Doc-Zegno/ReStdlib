#pragma once

#include "Utils/Builder.h"
#include "Iterable.h"


namespace ReLang {
	namespace Utils {
		template<typename T>
		Ptr<String> join(const Char* separator, Ptr<Iterable<T>> items, const Char* prefix = L"", const Char* suffix = L"") {
			auto builder = std::wostringstream();
			builder << prefix;
			auto iterator = items->getIterator();
			auto isFirst = true;
			while (iterator->moveNext()) {
				auto current = iterator->getCurrent();
				if (!isFirst) {
					builder << separator;
				}
				appendToBuilder(builder, toString(current, true));
				isFirst = false;
			}
			builder << suffix;
			return makeStringFromBuilder(builder);
		}


		template<typename U, typename V>
		Ptr<String> joinPairs(const Char* separator, Ptr<Iterable<Tuple<U, V>>> pairs, const Char* prefix = L"", const Char* suffix = L"") {
			auto builder = std::wostringstream();
			builder << prefix;
			auto iterator = pairs->getIterator();
			auto isFirst = true;
			while (iterator->moveNext()) {
				auto pair = iterator->getCurrent();
				if (!isFirst) {
					builder << separator;
				}
				appendToBuilder(builder, toString(pair.getFirst(), true));
				builder << L": ";
				appendToBuilder(builder, toString(pair.getSecond(), true));
				isFirst = false;
			}
			builder << suffix;
			return makeStringFromBuilder(builder);
		}
	}
}
