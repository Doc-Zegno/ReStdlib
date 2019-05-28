#pragma once

#include "Ptr.h"
#include "Primitives.h"


namespace ReLang {
    namespace Utils {
        template<typename T>
        Bool equals(T t1, T t2) {
            return t1 == t2;
        }


        template<typename T>
        Bool equals(Ptr<T> t1, Ptr<T> t2) {
            if (t1.get() == t2.get()) {
                return true;
            } else {
                if (t1 && t2) {
                    return (*t1) == t2;
                } else {
                    return false;
                }
            }
        }


        template<typename T>
        struct EqualityComparator {
            Bool operator()(T t1, T t2) const {
                return equals(t1, t2);
            }
        };
    }
}