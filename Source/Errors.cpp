#include "BasicString.h"
#include "Errors.h"


namespace ReLang {
    IndexError::IndexError(Int requested, Int end)
        : Error(Ptr<String>(new String(L"Expected index from [0; " + std::to_wstring(end) + L") (got " + std::to_wstring(requested) + L")")))
    {
    }


    NotImplementedError::NotImplementedError(Ptr<String> message) : Error(message) {
    }
}