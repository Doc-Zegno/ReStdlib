#pragma once

#include <iostream>

#include "Primitives.h"
#include "Utils/OperatorUtils.h"
#include "Utils/Format.h"


namespace ReLang {
    template<typename T1, typename T2>
    class Tuple {
    private:
        T1 _t1;
        T2 _t2;

    public:
        Tuple() = default;
        Tuple(T1 t1, T2 t2) : _t1(t1), _t2(t2) {}

        T1 getFirst() {
            return _t1;
        }

        T2 getSecond() {
            return _t2;
        }

        Bool operator==(Tuple<T1, T2> other) {
            return Utils::equals(_t1, other._t1) && Utils::equals(_t2, other._t2);
        }

		Bool operator!=(Tuple<T1, T2> other) {
			return !Utils::equals(_t1, other._t1) || !Utils::equals(_t2, other._t2);
		}

		Ptr<String> toString(Bool isEscaped = false) {
			return Utils::format(L'(', ReLang::toString(_t1, true), L", ", ReLang::toString(_t2, true), L')');
		}

		template<Int dummy = 0>
		Bool operator<(Tuple<T1, T2> other) {
			return _t1 < other._t1
				|| _t1 == other._t1 && _t2 < other._t2;
		}

		template<Int dummy = 0>
		Bool operator>(Tuple<T1, T2> other) {
			return _t1 > other._t1
				|| _t1 == other._t1 && _t2 > other._t2;
		}

		template<Int dummy = 0>
		Bool operator<=(Tuple<T1, T2> other) {
			return _t1 <= other._t1
				|| _t1 == other._t1 && _t2 <= other._t2;
		}

		template<Int dummy = 0>
		Bool operator>=(Tuple<T1, T2> other) {
			return _t1 >= other._t1
				|| _t1 == other._t1 && _t2 >= other._t2;
		}
    };


	template<typename T1, typename T2>
	Int compareTo(Tuple<T1, T2> x, Tuple<T1, T2> y) {
		auto cmp = compareTo(x.getFirst(), y.getFirst());
		if (cmp == 0) {
			return compareTo(x.getSecond(), y.getSecond());
		} else {
			return cmp;
		}
	}


	template<typename T1, typename T2>
	Tuple<T1, T2> makeTuple(T1 first, T2 second) {
		return Tuple<T1, T2>(first, second);
	}


    template<typename T1, typename T2>
    std::wostream& operator<<(std::wostream& out, Tuple<T1, T2> tuple) {
		auto representation = tuple.toString();
		out << representation->getRaw();
        return out;
    }
}
