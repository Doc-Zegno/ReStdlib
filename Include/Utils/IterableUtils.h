#pragma once

#include "Iterable.h"
#include "OperatorUtils.h"


namespace ReLang {
    namespace Utils {
        Int translateIndex(Int index, Int end);


        template<typename T>
        Bool iterableEquals(Ptr<Iterable<T>> ts1, Ptr<Iterable<T>> ts2) {
            if (ts1 && ts2) {
                if (ts1.get() == ts2.get()) {
                    return true;
                }

                if (ts1->getHasLength() && ts2->getHasLength()) {
                    if (ts1->getLength() != ts2->getLength()) {
                        return false;
                    }
                }

                auto iterator1 = ts1->getIterator();
                auto iterator2 = ts2->getIterator();
                while (iterator1->moveNext() && iterator2->moveNext()) {
                    if (!equals(iterator1->getCurrent(), iterator2->getCurrent())) {
                        return false;
                    }
                }

                if (!iterator1->moveNext() && !iterator2->moveNext()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }

        
        template<typename T>
        Bool contains(Ptr<Iterator<T>> iterator, T value) {
            while (iterator->moveNext()) {
                auto current = iterator->getCurrent();
                if (equals(current, value)) {
                    return true;
                }
            }
            return false;
        }
    }
}
