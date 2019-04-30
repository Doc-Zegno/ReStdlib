#pragma once

#include "Set.h"
#include "MutableIterable.h"


namespace ReLang {
    template<typename T>
    class MutableSet : public Set<T>, public MutableIterable<T> {
    public:
        virtual void add(T value) = 0;
        virtual void addAll(Ptr<Iterable<T>> values) = 0;
        virtual void remove(T value) = 0;
        virtual void removeAll(Ptr<Iterable<T>> values) = 0;
        virtual void clear() = 0;

        virtual Ptr<String> toString() override;
    };



    template<typename T>
    inline Ptr<String> MutableSet<T>::toString() {
        return Set<T>::toString();
    }
}
