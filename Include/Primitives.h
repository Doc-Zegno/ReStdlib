#pragma once

#include "Ptr.h"


namespace ReLang {
    using Void = void;
    using Int = int;
	using Float = double;
    using UInt = unsigned int;
    using Bool = bool;
    using Char = wchar_t;


	class String;


	class BoxedInt;


	Int divide(Int x, Int y);
	Int modulo(Int x, Int y);
	
	inline Float fdivide(Int x, Int y) {
		return Float(x) / Float(y);
	}


	Ptr<BoxedInt> box(Int value);


	template<typename Value>
	inline auto box(Value value) -> decltype(value.box()) {
		return value.box();
	}


	Ptr<String> toString(Int value, Bool isEscaped = false);


	template<typename T>
	inline Ptr<String> toString(T t, Bool isEscaped = false) {
		return t.toString(isEscaped);
	}


	template<typename T>
	inline Ptr<String> toString(Ptr<T> t, Bool isEscaped = false) {
		return t->toString(isEscaped);
	}


	int compareTo(Int x, Int y);
}
