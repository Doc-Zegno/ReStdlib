#pragma once

#include "Any.h"


namespace ReLang {
    template<typename TResult, typename... TArgs>
    class Function : public Any {
    public:
        virtual TResult operator()(TArgs... args) = 0;
    };
}
