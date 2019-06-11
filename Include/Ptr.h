#pragma once

#include <iostream>
#include <initializer_list>
#include <memory>


namespace ReLang {
    /*template<typename T>
    using Ptr = std::shared_ptr<T>;*/


    /*template<typename T>
    using WeakPtr = std::weak_ptr<T>;*/


	template<typename T>
	class Ptr : public std::shared_ptr<T> {
	public:
		using std::shared_ptr<T>::shared_ptr;
		using std::shared_ptr<T>::get;
		using std::shared_ptr<T>::operator->;
		using std::shared_ptr<T>::operator*;
		using std::shared_ptr<T>::operator bool;


		template<typename ...TArgs>
		auto operator()(TArgs ...args) -> decltype((*get())(args...)) {
			return (*get())(args...);
		}


		template<typename TArg>
		auto operator[](TArg arg) -> decltype((*get())[arg]) {
			return (*get())[arg];
		}
	};


    template<typename TObject, typename ...TArgs>
    inline Ptr<TObject> makePtr(TArgs&& ...args) {
        return Ptr<TObject>(new TObject(std::forward<TArgs>(args)...));
    }


    template<typename TObject, typename TArg>
    inline Ptr<TObject> makePtr(std::initializer_list<TArg> args) {
        return Ptr<TObject>(new TObject(args));
    }


	template<typename To, typename From>
	inline Ptr<To> staticPointerCast(Ptr<From> from) {
		return std::static_pointer_cast<To>(from);
	}


	template<typename U, typename V>
	bool operator==(Ptr<U> x, Ptr<V> y) {
		// TODO: maybe you should add null checks
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> Equality test! Serious business! <!>\n";
		return (*x) == y;
	}


	template<typename U, typename V>
	bool operator!=(Ptr<U> x, Ptr<V> y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> Inequality test! Serious business! <!>\n";
		return (*x) != y;
	}


	template<typename U, typename V>
	bool operator>(Ptr<U> x, Ptr<V> y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> GT test! Serious business! <!>\n";
		return (*x) > y;
	}


	template<typename U, typename V>
	bool operator<(Ptr<U> x, Ptr<V> y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> LT test! Serious business! <!>\n";
		return (*x) < y;
	}


	template<typename U, typename V>
	bool operator>=(Ptr<U> x, Ptr<V> y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> GE test! Serious business! <!>\n";
		return (*x) >= y;
	}


	template<typename U, typename V>
	bool operator<=(Ptr<U> x, Ptr<V> y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> LE test! Serious business! <!>\n";
		return (*x) <= y;
	}


	template<typename U, typename V>
	auto operator+(Ptr<U> x, Ptr<V> y) -> decltype((*x) + y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> Addition! Serious business! <!>\n";
		return (*x) + y;
	}


	template<typename U, typename V>
	auto operator-(Ptr<U> x, Ptr<V> y) -> decltype((*x) - y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> Subtraction! Serious business! <!>\n";
		return (*x) - y;
	}


	template<typename U, typename V>
	auto operator*(Ptr<U> x, Ptr<V> y) -> decltype((*x) * y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> Multiplication! Serious business! <!>\n";
		return (*x) * y;
	}


	template<typename U, typename V>
	auto operator/(Ptr<U> x, Ptr<V> y) -> decltype((*x) / y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> Division! Serious business! <!>\n";
		return (*x) / y;
	}


	template<typename U, typename V>
	auto operator%(Ptr<U> x, Ptr<V> y) -> decltype((*x) % y) {
		// Propagation through Ptr<T> to instance of Equatable<T>
		// WARNING: reference equality of Ptr's is not valid anymore!
		std::wcout << "<!> Modulo! Serious business! <!>\n";
		return (*x) % y;
	}

	
	template<typename T>
	struct IsPtr : std::false_type {};


	template<typename T>
	struct IsPtr<Ptr<T>> : std::true_type {};
}
