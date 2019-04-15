#include "BasicString.h"
#include "Errors.h"
#include "Any.h"


namespace ReLang {
    Ptr<String> Any::toString() {
        throw NotImplementedError(Ptr<String>(new String(L"This class does not implement toString()")));
    }
}
