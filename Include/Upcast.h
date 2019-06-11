#pragma once

#include "Primitives.h"


namespace ReLang {
	template<typename E, typename F>
	auto upcastPtr(Ptr<F> f) -> typename std::enable_if<std::is_base_of<E, F>::value, Ptr<E>>::type {
		return f;
	}


	template<typename E, typename F>
	auto upcastPtr(Ptr<F> f) -> typename std::enable_if<!std::is_base_of<E, F>::value, Ptr<E>>::type {
		return E::upcast(f);
	}


	template<typename E>
	E upcast(E e) {
		return e;
	}


	template<typename E, typename F>
	auto upcast(F f) -> typename std::enable_if<!std::is_same<E, F>::value /*&& !std::is_function<F>::value*/ && IsPtr<E>::value && !IsPtr<F>::value, E>::type {
		return upcastPtr<typename E::element_type>(box(f));
	}


	/*template<typename E, typename TResult, typename ...TArgs>
	E upcast(TResult f(TArgs...)) {
		return upcastPtr<typename E::element_type>(boxFunction(f));
	}*/


	template<typename E, typename F>
	auto upcast(F f) -> typename std::enable_if<!std::is_same<E, F>::value && IsPtr<E>::value && IsPtr<F>::value, E>::type {
		return upcastPtr<typename E::element_type>(f);
	}
}