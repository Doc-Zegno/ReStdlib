#pragma once

#include "Primitives.h"
#include "Iterable.h"
#include "Equatable.h"


namespace ReLang {
    template<typename T>
    class List : public virtual Iterable<T>, public virtual Equatable<List<T>> {
    public:
        virtual T get(Int index) = 0;
        virtual Ptr<List<T>> getSlice(Int start, Int end, Int step) = 0;

        virtual Bool operator==(Ptr<List<T>> other) override;
        virtual Ptr<String> toString(Bool isEscaped = false) override;
    };



    template<typename T>
    inline Bool List<T>::operator==(Ptr<List<T>> other) {
        auto otherPtr = Ptr<Iterable<T>>(other);
        return Utils::iterableEquals(this->getSelf(), otherPtr);
    }


    template<typename T>
    inline Ptr<String> List<T>::toString(Bool isEscaped) {
        return Utils::join(L", ", this->getSelf(), L"[", L"]");
    }
}
