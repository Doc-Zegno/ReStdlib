#pragma once

#include "Tuple.h"
#include "Comparable.h"
#include "Errors.h"


namespace ReLang {
	namespace UncheckedComparisonUtils {
		/*template<typename T>
		Bool operator<(T x, T y) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		Bool operator>(T x, T y) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		Bool operator<=(T x, T y) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		Bool operator>=(T x, T y) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		Bool operator==(T x, T y) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		Bool operator!=(T x, T y) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}*/

		template<typename T>
		auto lessThan(T x, T y, int dummy) -> decltype(x < y, Bool()) {
			return x < y;
		}
		
		template<typename T>
		Bool lessThan(T x, T y, long dummy) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		auto greaterThan(T x, T y, int dummy) -> decltype(x > y, Bool()) {
			return x > y;
		}

		template<typename T>
		Bool greaterThan(T x, T y, long dummy) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		auto lessOrEqual(T x, T y, Int dummy) -> decltype(x <= y, Bool()) {
			return x <= y;
		}

		template<typename T>
		Bool lessOrEqual(T x, T y, long dummy) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		auto greaterOrEqual(T x, T y, int dummy) -> decltype(x >= y, Bool()) {
			return x >= y;
		}

		template<typename T>
		Bool greaterOrEqual(T x, T y, long dummy) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		auto equals(T x, T y, int dummy) -> decltype(x == y, Bool()) {
			return x == y;
		}

		template<typename T>
		Bool equals(T x, T y, long dummy) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}

		template<typename T>
		auto compare(T x, T y, int dummy) -> decltype(compareTo(x, y), Int()) {
			return compareTo(x, y);
		}

		template<typename T>
		Int compare(T x, T y, long dummy) {
			throw NotSupportedError(L"Comparison is not supported for this type");
		}
	}


	template<typename T1, typename T2>
	class BoxedTuple : public virtual Comparable<BoxedTuple<T1, T2>> {
	private:
		T1 _t1;
		T2 _t2;

	public:
		BoxedTuple(T1 t1, T2 t2) : _t1(t1), _t2(t2) {}

		T1 getFirst() {
			return _t1;
		}

		T2 getSecond() {
			return _t2;
		}

		Tuple<T1, T2> unbox() {
			return makeTuple(_t1, _t2);
		}

		virtual Ptr<String> toString(Bool isEscaped = false) override {
			return Utils::format(L'(', ReLang::toString(_t1, true), L", ", ReLang::toString(_t2, true), L')');
		}

		virtual Bool operator==(Ptr<BoxedTuple<T1, T2>> other) override {
			return UncheckedComparisonUtils::equals(_t1, other->_t1, 0) && UncheckedComparisonUtils::equals(_t2, other->_t2, 0);
		}

		virtual Bool operator!=(Ptr<BoxedTuple<T1, T2>> other) override {
			return !UncheckedComparisonUtils::equals(_t1, other->_t1, 0) || !UncheckedComparisonUtils::equals(_t2, other->_t2, 0);
		}

		virtual Bool operator<(Ptr<BoxedTuple<T1, T2>> other) override {
			return UncheckedComparisonUtils::lessThan(_t1, other->_t1, 0)
				|| UncheckedComparisonUtils::equals(_t1, other->_t1, 0) && UncheckedComparisonUtils::lessThan(_t2, other->_t2, 0);
		}

		virtual Bool operator>(Ptr<BoxedTuple<T1, T2>> other) override {
			return UncheckedComparisonUtils::greaterThan(_t1, other->_t1, 0)
				|| UncheckedComparisonUtils::equals(_t1, other->_t1, 0) && UncheckedComparisonUtils::greaterThan(_t2, other->_t2, 0);
		}

		virtual Bool operator<=(Ptr<BoxedTuple<T1, T2>> other) override {
			return UncheckedComparisonUtils::lessOrEqual(_t1, other->_t1, 0)
				|| UncheckedComparisonUtils::equals(_t1, other->_t1, 0) && UncheckedComparisonUtils::lessOrEqual(_t2, other->_t2, 0);
		}

		virtual Bool operator>=(Ptr<BoxedTuple<T1, T2>> other) override {
			return UncheckedComparisonUtils::greaterOrEqual(_t1, other->_t1, 0)
				|| UncheckedComparisonUtils::equals(_t1, other->_t1, 0) && UncheckedComparisonUtils::greaterOrEqual(_t2, other->_t2, 0);
		}

		virtual Int compareTo(Ptr<BoxedTuple<T1, T2>> other) override {
			auto cmp = UncheckedComparisonUtils::compare(_t1, other->_t1, 0);
			if (cmp == 0) {
				return UncheckedComparisonUtils::compare(_t2, other->_t2, 0);
			} else {
				return cmp;
			}
		}
	};


	template<typename T1, typename T2>
	Ptr<BoxedTuple<T1, T2>> box(Tuple<T1, T2> tuple) {
		return makePtr<BoxedTuple<T1, T2>>(tuple.getFirst(), tuple.getSecond());
	}
}
