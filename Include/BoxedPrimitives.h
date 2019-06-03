#pragma once

#include "Comparable.h"
#include "Numeric.h"


namespace ReLang {
	class BoxedInt : public virtual Comparable<BoxedInt>, public virtual Numeric<BoxedInt> {
	private:
		Int _value;

	public:
		BoxedInt() : _value(0) {}
		BoxedInt(Int value) : _value(value) {}

		virtual Ptr<BoxedInt> operator+(Ptr<BoxedInt> other) override {
			return makePtr<BoxedInt>(_value + other->_value);
		}

		virtual Ptr<BoxedInt> operator-(Ptr<BoxedInt> other) override {
			return makePtr<BoxedInt>(_value - other->_value);
		}

		virtual Ptr<BoxedInt> operator*(Ptr<BoxedInt> other) override {
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


	class BoxedFloat : public virtual Comparable<BoxedFloat>, public virtual Numeric<BoxedFloat> {
	private:
		Float _value;

	public:
		BoxedFloat() : _value(0.0) {}
		BoxedFloat(Float value) : _value(value) {}

		virtual Ptr<BoxedFloat> operator+(Ptr<BoxedFloat> other) override {
			return makePtr<BoxedFloat>(_value + other->_value);
		}

		virtual Ptr<BoxedFloat> operator-(Ptr<BoxedFloat> other) override {
			return makePtr<BoxedFloat>(_value - other->_value);
		}

		virtual Ptr<BoxedFloat> operator*(Ptr<BoxedFloat> other) override {
			return makePtr<BoxedFloat>(_value * other->_value);
		}

		Ptr<BoxedFloat> operator/(Ptr<BoxedFloat> other) {
			return makePtr<BoxedFloat>(_value / other->_value);
		}

		Float unbox() {
			return _value;
		}

		virtual Ptr<String> toString(Bool isEscaped = false) override {
			return ReLang::toString(_value, isEscaped);
		}

		virtual Bool operator==(Ptr<BoxedFloat> other) override {
			return _value == other->_value;
		}

		virtual Bool operator!=(Ptr<BoxedFloat> other) override {
			return _value != other->_value;
		}

		virtual Bool operator>(Ptr<BoxedFloat> other) override {
			return _value > other->_value;
		}

		virtual Bool operator<(Ptr<BoxedFloat> other) override {
			return _value < other->_value;
		}

		virtual Bool operator>=(Ptr<BoxedFloat> other) override {
			return _value >= other->_value;
		}

		virtual Bool operator<=(Ptr<BoxedFloat> other) override {
			return _value <= other->_value;
		}

		virtual Int compareTo(Ptr<BoxedFloat> other) override {
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


	class BoxedChar : public virtual Comparable<BoxedChar> {
	private:
		Char _value;

	public:
		BoxedChar() : _value(L'\0') {}
		BoxedChar(Char value) : _value(value) {}

		Char unbox() {
			return _value;
		}

		virtual Ptr<String> toString(Bool isEscaped = false) override {
			return ReLang::toString(_value, isEscaped);
		}

		virtual Bool operator==(Ptr<BoxedChar> other) override {
			return _value == other->_value;
		}

		virtual Bool operator!=(Ptr<BoxedChar> other) override {
			return _value != other->_value;
		}

		virtual Bool operator>(Ptr<BoxedChar> other) override {
			return _value > other->_value;
		}

		virtual Bool operator<(Ptr<BoxedChar> other) override {
			return _value < other->_value;
		}

		virtual Bool operator>=(Ptr<BoxedChar> other) override {
			return _value >= other->_value;
		}

		virtual Bool operator<=(Ptr<BoxedChar> other) override {
			return _value <= other->_value;
		}

		virtual Int compareTo(Ptr<BoxedChar> other) override {
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


	class BoxedBool : public virtual Any {
	private:
		Bool _value;

	public:
		BoxedBool() : _value(false) {}
		BoxedBool(Bool value) : _value(value) {}

		Bool unbox() {
			return _value;
		}

		virtual Ptr<String> toString(Bool isEscaped = false) override {
			return ReLang::toString(_value, isEscaped);
		}
	};


	inline Ptr<BoxedInt> divide(Ptr<BoxedInt> x, Ptr<BoxedInt> y) {
		return makePtr<BoxedInt>(divide(x->unbox(), y->unbox()));
	}


	inline Ptr<BoxedInt> modulo(Ptr<BoxedInt> x, Ptr<BoxedInt> y) {
		return makePtr<BoxedInt>(modulo(x->unbox(), y->unbox()));
	}


	inline Ptr<BoxedFloat> fdivide(Ptr<BoxedInt> x, Ptr<BoxedInt> y) {
		return makePtr<BoxedFloat>(fdivide(x->unbox(), y->unbox()));
	}
}
