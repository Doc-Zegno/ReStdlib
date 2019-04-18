#pragma once

#include "Error.h"
#include "Primitives.h"


namespace ReLang {
    class IndexError : public Error {
    public:
        IndexError(Int requested, Int end);
    };


    class NotImplementedError : public Error {
    public:
        NotImplementedError(const Char* message);
        NotImplementedError(Ptr<String> message = Ptr<String>());
    };


    class InvalidIteratorError : public Error {
    public:
        InvalidIteratorError(const Char* message);
        InvalidIteratorError(Ptr<String> message = Ptr<String>());
    };


    class EmptyIterableError : public Error {
    public:
        EmptyIterableError();
    };


    class ValueError : public Error {
    public:
        ValueError(const Char* message);
        ValueError(Ptr<String> message);
    };
}
