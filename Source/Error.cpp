#include "Error.h"


namespace ReLang {
    Error::Error(Ptr<String> message) : _message(message) {
    }


    Ptr<String> Error::getMessage() {
        return _message;
    }


    Ptr<String> Error::toString() {
        return _message;
    }
}