#include "BasicString.h"
#include "Errors.h"


namespace ReLang {
    IndexError::IndexError(Int requested, Int end)
        : Error(Ptr<String>(
            new String(
                L"Expected index from [-" 
                + std::to_wstring(end) 
                + L"; " 
                + std::to_wstring(end) 
                + L") (got " + std::to_wstring(requested) 
                + L")")))
    {
    }


    NotImplementedError::NotImplementedError(const Char* message)
        : Error(message ? makePtr<String>(message) : makePtr<String>(L"This method is not implemented"))
    {
    }


    NotImplementedError::NotImplementedError(Ptr<String> message)
        : Error(message ? message : makePtr<String>(L"This method is not implemented"))
    {
    }


    InvalidIteratorError::InvalidIteratorError(const Char* message)
        : Error(message ? makePtr<String>(message) : makePtr<String>(L"Trying to access element with invalid iterator"))
    {
    }


    InvalidIteratorError::InvalidIteratorError(Ptr<String> message)
        : Error(message ? message : makePtr<String>(L"Trying to access element with invalid iterator"))
    {
    }


    EmptyIterableError::EmptyIterableError() : Error(makePtr<String>(L"This iterable is empty")) {
    }


    ValueError::ValueError(const Char* message)
        : Error(message ? makePtr<String>(message) : makePtr<String>(L"Invalid value was provided"))
    {
    }


    ValueError::ValueError(Ptr<String> message)
        : Error(message ? message : makePtr<String>(L"Invalid value was provided"))
    {
    }
}