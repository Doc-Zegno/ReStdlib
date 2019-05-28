#pragma once

#include "Any.h"
#include "Primitives.h"


namespace ReLang {
    class Error : public Any {
    private:
        Ptr<String> _message;

    public:
        Error(const Char* message);
        Error(Ptr<String> message);

        virtual Ptr<String> getMessage();

        virtual Ptr<String> toString(Bool isEscaped = false) override;
    };
}
