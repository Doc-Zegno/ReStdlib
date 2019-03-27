#pragma once

#include "Any.h"


namespace ReLang {
    template<typename TResult, typename... TArgs>
    class Function : public Any {
    public:
        virtual TResult __call__(TArgs... args) = 0;
    };
}
