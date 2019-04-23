#pragma once

#include "Iterator.h"


namespace ReLang {
    template<typename T>
    class MutatingIterator : public Iterator<T> {
    public:
        virtual void setCurrent(T value) = 0;
    };
}
