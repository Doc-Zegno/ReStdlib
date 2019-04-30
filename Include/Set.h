#pragma once

#include "Iterable.h"
#include "Equatable.h"


namespace ReLang {
    template<typename T>
    class Set : public virtual Iterable<T>, public Equatable<Set<T>> {
    public:
        virtual Ptr<Set<T>> unioned(Ptr<Iterable<T>> items) = 0;
        virtual Ptr<Set<T>> intersection(Ptr<Iterable<T>> items) = 0;
        virtual Ptr<Set<T>> difference(Ptr<Iterable<T>> items) = 0;

        virtual Bool operator==(Ptr<Set<T>> other) override;
        virtual Ptr<String> toString() override;
    };



    template<typename T>
    inline Bool Set<T>::operator==(Ptr<Set<T>> other) {
        if (this->getHasLength() && other->getHasLength()) {
            if (this->getLength() != other->getLength()) {
                return false;
            }
        }

        auto iterator = other->getIterator();
        while (iterator->moveNext()) {
            if (!this->contains(iterator->getCurrent())) {
                return false;
            }
        }

        return true;
    }


    template<typename T>
    inline Ptr<String> Set<T>::toString() {
        return Utils::join(L", ", this->getSelf(), L"{", L"}");
    }
}
