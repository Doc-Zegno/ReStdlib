#pragma once

#include "Iterable.h"
#include "Primitives.h"


namespace ReLang {
    template<typename T>
    class List : public Iterable<T> {
    public:
        virtual T get(Int index) = 0;

        virtual Ptr<String> toString() override;
    };



    template<typename T>
    inline Ptr<String> List<T>::toString() {
        return Utils::join(L", ", this->getSelf(), L"[", L"]");
    }
}
