#pragma once

#include "Iterable.h"
#include "MutatingIterator.h"


namespace ReLang {
    template<typename T>
    class MutableIterable : public virtual Iterable<T> {
    public:
        virtual Ptr<MutatingIterator<T>> getMutatingIterator() = 0;

        template<typename Es, typename E>
        void zipInPlace(Ptr<Es> items, Ptr<Function<T, T, E>> operation);
    };



    template<typename T>
    template<typename Es, typename E>
    inline void MutableIterable<T>::zipInPlace(Ptr<Es> items, Ptr<Function<T, T, E>> operation) {
        auto thisIterable = getMutatingIterator();
        auto thatIterable = items->getIterator();
        while (thisIterable->moveNext() && thatIterable->moveNext()) {
            auto x = thisIterable->getCurrent();
            auto y = thatIterable->getCurrent();
            auto result = (*operation)(x, y);
            thisIterable->setCurrent(result);
        }
    }
}
