#ifndef LIST_H
#define LIST_H

#include "Iterable.h"
#include "Primitives.h"


namespace ReLang {
    template<typename T>
    class List : public Iterable<T> {
    public:
        virtual T __get__(Int index) = 0;
    };
}


#endif
