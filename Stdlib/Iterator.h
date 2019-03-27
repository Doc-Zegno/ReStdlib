#pragma once

#include "Any.h"


namespace ReLang {
    template<typename T>
    class Iterator : public Any {
    public:
        virtual T getCurrent() = 0;
        virtual bool moveNext() = 0;
    };
}

