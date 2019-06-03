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
	class BoxedFloat;
	class BoxedBool;
	class BoxedChar;


	Int divide(Int x, Int y);
	Int modulo(Int x, Int y);
	
	inline Float fdivide(Int x, Int y) {
		return Float(x) / Float(y);
	}


	Ptr<BoxedInt> box(Int value);
	Ptr<BoxedFloat> box(Float value);
	Ptr<BoxedBool> box(Bool value);
	Ptr<BoxedChar> box(Char value);


	template<typename Value>
	inline auto box(Value value) -> decltype(value.box()) {
		return value.box();
	}


	Ptr<String> makeNullStr();
	Ptr<String> toString(Int value, Bool isEscaped = false);
	Ptr<String> toString(Float value, Bool isEscaped = false);
	Ptr<String> toString(Char value, Bool isEscaped = false);
	Ptr<String> toString(Bool value, Bool isEscaped = false);
	Ptr<String> toString(const Char* value, Bool isEscaped = false);


	template<typename T>
	inline Ptr<String> toString(T t, Bool isEscaped = false) {
		return t.toString(isEscaped);
	}


	template<typename T>
	inline Ptr<String> toString(Ptr<T> t, Bool isEscaped = false) {
		if (t) {
			return t->toString(isEscaped);
		} else {
			return makeNullStr();
		}
	}


	Int compareTo(Int x, Int y);
	Int compareTo(Float x, Float y);
	Int compareTo(Char x, Char y);


	template<typename T>
	inline Int compareTo(Ptr<T> x, Ptr<T> y) {
		return x->compareTo(y);
	}
}
