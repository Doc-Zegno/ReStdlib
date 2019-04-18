#include "Print.h"

#include "BasicString.h"


namespace ReLang {
    void print(Ptr<Any> any, const Char* end) {
        if (any) {
            auto representation = any->toString();
            auto& raw = representation->getRaw();
            std::wcout << raw;
        } else {
            std::wcout << L"null";
        }
        std::wcout << end;
    }
}
