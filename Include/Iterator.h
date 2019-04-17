#pragma once

#include "Cloneable.h"


namespace ReLang {
    template<typename T>
    class Iterator : public Cloneable<Iterator<T>> {
    public:
        virtual T getCurrent() = 0;
        virtual bool moveNext() = 0;
    };
}
