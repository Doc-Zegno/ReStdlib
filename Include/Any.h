#pragma once

#include "Ptr.h"
#include "Primitives.h"


namespace ReLang {
    class Any {
    public:
        virtual Ptr<String> toString(Bool isEscaped = false);

        virtual ~Any() { }
    };
}
