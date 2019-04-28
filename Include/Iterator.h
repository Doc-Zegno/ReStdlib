#pragma once

#include "Any.h"
#include "Cloneable.h"
#include "Primitives.h"


namespace ReLang {
    template<typename T>
    class Iterator : public Any, public Cloneable<Iterator<T>> {
    public:
        virtual T getCurrent() = 0;
        virtual Bool moveNext() = 0;
    };
}
