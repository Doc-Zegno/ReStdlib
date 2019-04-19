#pragma once

#include <iostream>


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

        // TODO: implement .toString()
    };


    template<typename T1, typename T2>
    std::wostream& operator<<(std::wostream& out, Tuple<T1, T2>& tuple) {
        // TODO: replace with .toString() invocation
        out << L'(' << tuple.getFirst() << L", " << tuple.getSecond() << L')';
        return out;
    }
}