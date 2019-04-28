#pragma once

#include "Iterable.h"


namespace ReLang {
    template<typename T>
    class Set : public virtual Iterable<T> {
    public:
        virtual Ptr<String> toString() override;
    };



    template<typename T>
    inline Ptr<String> Set<T>::toString() {
        return Utils::join(L", ", this->getSelf(), L"{", L"}");
    }
}
