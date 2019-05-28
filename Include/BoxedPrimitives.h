#pragma once

#include "Comparable.h"


namespace ReLang {
	class BoxedInt : public virtual Comparable<BoxedInt> {
	private:
		Int _value;

	public:
		BoxedInt() : _value(0) {}
		BoxedInt(Int value) : _value(value) {}

		Ptr<BoxedInt> operator+(Ptr<BoxedInt> other) {
			return makePtr<BoxedInt>(_value + other->_value);
		}

		Ptr<BoxedInt> operator-(Ptr<BoxedInt> other) {
			return makePtr<BoxedInt>(_value - other->_value);
		}

		Ptr<BoxedInt> operator*(Ptr<BoxedInt> other) {
			return makePtr<BoxedInt>(_value * other->_value);
		}

		Ptr<BoxedInt> operator/(Ptr<BoxedInt> other) {
			return makePtr<BoxedInt>(_value / other->_value);
		}

		Ptr<BoxedInt> operator%(Ptr<BoxedInt> other) {
			return makePtr<BoxedInt>(_value % other->_value);
		}

		Int unbox() {
			return _value;
		}

		virtual Ptr<String> toString(Bool isEscaped = false) override {
			return ReLang::toString(_value, isEscaped);
		}

		virtual Bool operator==(Ptr<BoxedInt> other) override {
			return _value == other->_value;
		}

		virtual Bool operator!=(Ptr<BoxedInt> other) override {
			return _value != other->_value;
		}

		virtual Bool operator>(Ptr<BoxedInt> other) override {
			return _value > other->_value;
		}

		virtual Bool operator<(Ptr<BoxedInt> other) override {
			return _value < other->_value;
		}

		virtual Bool operator>=(Ptr<BoxedInt> other) override {
			return _value >= other->_value;
		}

		virtual Bool operator<=(Ptr<BoxedInt> other) override {
			return _value <= other->_value;
		}

		virtual Int compareTo(Ptr<BoxedInt> other) override {
			auto otherValue = other->_value;
			if (_value > otherValue) {
				return 1;
			} else if (_value < otherValue) {
				return -1;
			} else {
				return 0;
			}
		}
	};


	inline Ptr<BoxedInt> divide(Ptr<BoxedInt> x, Ptr<BoxedInt> y) {
		return makePtr<BoxedInt>(divide(x->unbox(), y->unbox()));
	}


	inline Ptr<BoxedInt> modulo(Ptr<BoxedInt> x, Ptr<BoxedInt> y) {
		return makePtr<BoxedInt>(modulo(x->unbox(), y->unbox()));
	}


	// TODO: reimplement with BoxedFloat
	/*inline Ptr<BoxedInt> fdiv(Ptr<BoxedInt> x, Ptr<BoxedInt> y) {
		return makePtr<BoxedInt>(fdiv(x->unbox(), y->unbox()));
	}*/
}
