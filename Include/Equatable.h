#pragma once

#include "Ptr.h"
#include "Primitives.h"


namespace ReLang {
    template<typename T>
    class Equatable {
    public:
        virtual Bool operator==(Ptr<T> other) = 0;
    };
}
