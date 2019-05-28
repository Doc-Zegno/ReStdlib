#pragma once

#include "List.h"
#include "MutableIterable.h"


namespace ReLang {
    template<typename T>
    class MutableList : public List<T>, public MutableIterable<T> {
    public:
        virtual Ptr<MutableList<T>> getMutableSlice(Int start, Int end, Int step) = 0;

        virtual void set(Int index, T value) = 0;
        virtual void add(T value) = 0;
        virtual void addAll(Ptr<Iterable<T>> values) = 0;
        virtual void insertAt(Int index, T value) = 0;
        virtual void removeAt(Int index) = 0;
        virtual void clear() = 0;
        virtual void resize(Int size, T value = T()) = 0;

        virtual Ptr<String> toString(Bool isEscaped = false) override;
    };



    template<typename T>
    inline Ptr<String> MutableList<T>::toString(Bool isEscaped) {
        return List<T>::toString(isEscaped);
    }
}
