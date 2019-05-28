#include "Error.h"
#include "BasicString.h"


namespace ReLang {
    Error::Error(const Char* message) : _message(makePtr<String>(message)) {
    }


    Error::Error(Ptr<String> message) : _message(message) {
    }


    Ptr<String> Error::getMessage() {
        return _message;
    }


    Ptr<String> Error::toString(Bool isEscaped) {
        return _message;
    }
}