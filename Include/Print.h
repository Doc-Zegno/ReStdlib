#pragma once

#include <iostream>

#include "Any.h"
#include "Primitives.h"


namespace ReLang {
    template<typename T>
    void print(T t, const Char* end = L"\n") {
        std::wcout << t << end;
    }


    void print(Ptr<Any> any, const Char* end = L"\n");


    template<typename T>
    void print(Ptr<T> t, const Char* end = L"\n") {
        auto ptr = std::reinterpret_pointer_cast<Any>(t);
        print(ptr, end);
    }


    template<typename T>
    void printAll(T t) {
        print(t);
    }


    template<typename T1, typename T2, typename ...TArgs>
    void printAll(T1 t1, T2 t2, TArgs ...args) {
        print(t1, L" ");
        printAll(t2, args...);
    } 
}
