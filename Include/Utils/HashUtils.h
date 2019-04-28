#pragma once

#include <functional>

#include "Primitives.h"


namespace ReLang {
    namespace Utils {
        template<typename Key>
        inline UInt getHashCode(Key key) {
            return std::hash<Key>()(key);
        }


        template<typename Key>
        struct Hash {
            UInt operator()(Key key) const {
                return getHashCode(key);
            }
        };
    }
}
