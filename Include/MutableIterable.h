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

        virtual void sortWithInPlace(Ptr<Function<Bool, T, T>> comparator);

        template<typename K>
        void sortByInPlace(Ptr<Function<K, T>> key, Bool isAscending = true);

        template<Int dummy = 0>
        void sortInPlace(Bool isAscending = true);
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


    template<typename T>
    template<typename K>
    inline void MutableIterable<T>::sortByInPlace(Ptr<Function<K, T>> key, Bool isAscending) {
        if (isAscending) {
            sortWithInPlace(Ptr<Function<Bool, T, T>>(new Utils::AscendingKeyComparator<K, T>(key)));
        } else {
            sortWithInPlace(Ptr<Function<Bool, T, T>>(new Utils::DescendingKeyComparator<K, T>(key)));
        }
    }


    template<typename T>
    template<Int dummy>
    inline void MutableIterable<T>::sortInPlace(Bool isAscending) {
        if (isAscending) {
            sortWithInPlace(Ptr<Function<Bool, T, T>>(new Utils::AscendingComparator<T>()));
        } else {
            sortWithInPlace(Ptr<Function<Bool, T, T>>(new Utils::DescendingComparator<T>()));
        }
    }


    template<typename T>
    inline void MutableIterable<T>::sortWithInPlace(Ptr<Function<Bool, T, T>> comparator) {
        auto vector = std::vector<T>();
        if (this->getHasLength()) {
            vector.reserve(this->getLength());
        }

        auto iterator = this->getIterator();
        while (iterator->moveNext()) {
            vector.push_back(iterator->getCurrent());
        }

        std::sort(vector.begin(), vector.end(), [comparator](T t1, T t2) {
            return (*comparator)(t1, t2);
        });

        auto index = 0;
        auto mutatingIterator = getMutatingIterator();
        while (mutatingIterator->moveNext()) {
            mutatingIterator->setCurrent(vector[index]);
            index++;
        }
    }
}
