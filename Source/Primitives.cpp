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


	Ptr<String> toString(Int value, Bool isEscaped) {
		auto raw = std::to_wstring(value);
		return makePtr<String>(std::move(raw));
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
