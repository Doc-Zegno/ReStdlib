#include "Primitives.h"

#include "BasicString.h"
#include "BoxedPrimitives.h"


namespace ReLang {
	Int divide(Int x, Int y) {
		if (y != 0) {
			return x / y;
		} else {
			throw ZeroDivisionError();
		}
	}


	Int modulo(Int x, Int y) {
		if (y != 0) {
			return x % y;
		} else {
			throw ZeroDivisionError();
		}
	}


	Ptr<BoxedInt> box(Int value) {
		return makePtr<BoxedInt>(value);
	}


	Ptr<String> makeNullStr() {
		return Ptr<String>();
	}


	Ptr<String> toString(Int value, Bool isEscaped) {
		auto raw = std::to_wstring(value);
		return makePtr<String>(std::move(raw));
	}


	Ptr<String> toString(Char value, Bool isEscaped) {
		if (isEscaped) {
			Char buffer[5] = L"'?";
			
			// Escape
			auto end = Utils::escapeChar(value, buffer + 1, true);
			*end = L'\'';

			auto raw = std::wstring(buffer);
			return makeStr(std::move(raw));
		} else {
			auto raw = std::wstring(1, value);
			return makeStr(std::move(raw));
		}
	}


	Ptr<String> toString(Bool value, Bool isEscaped) {
		auto string = value ? L"true" : L"false";
		return makeStr(string);
	}


	Ptr<String> toString(const Char* value, Bool isEscaped) {
		// TODO: implement escaping
		auto raw = std::wstring(value);
		return makeStr(std::move(raw));
	}


	int compareTo(Int x, Int y) {
		if (x < y) {
			return -1;
		} else if (x > y) {
			return 1;
		} else {
			return 0;
		}
	}
}
