#pragma once

#include "Iterable.h"


namespace ReLang {
    template<typename T>
    class Set : public virtual Iterable<T> {
    public:
        virtual Ptr<Set<T>> unioned(Ptr<Iterable<T>> items) = 0;
        virtual Ptr<Set<T>> intersection(Ptr<Iterable<T>> items) = 0;
        virtual Ptr<Set<T>> difference(Ptr<Iterable<T>> items) = 0;

        virtual Ptr<String> toString() override;
    };



    template<typename T>
    inline Ptr<String> Set<T>::toString() {
        return Utils::join(L", ", this->getSelf(), L"{", L"}");
    }
}
