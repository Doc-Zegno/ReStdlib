#pragma once

#include "Any.h"


namespace ReLang {
    template<typename T>
    class Cloneable : public Any {
    public:
        virtual Ptr<T> clone() = 0;
    };
}
