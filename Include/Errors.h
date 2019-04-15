#ifndef ERRORS_H
#define ERRORS_H

#include "Error.h"
#include "Primitives.h"


namespace ReLang {
    class IndexError : public Error {
    public:
        IndexError(Int requested, Int end);
    };


    class NotImplementedError : public Error {
    public:
        NotImplementedError(Ptr<String> message);
    };
}


#endif