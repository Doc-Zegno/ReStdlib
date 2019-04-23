#pragma once

#include "List.h"
#include "MutableIterable.h"


namespace ReLang {
    template<typename T>
    class MutableList : public List<T>, public MutableIterable<T> {
    public:
        virtual void set(Int index, T value) = 0;

        virtual Ptr<String> toString() override;
    };



    template<typename T>
    inline Ptr<String> MutableList<T>::toString() {
        return List<T>::toString();
    }
}
