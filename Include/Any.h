#pragma once

#include "Ptr.h"


namespace ReLang {
    class String;

    class Any {
    public:
        virtual Ptr<String> toString();

        virtual ~Any() { }
    };
}
