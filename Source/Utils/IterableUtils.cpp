#include "Utils/IterableUtils.h"
#include "Errors.h"


namespace ReLang {
    namespace Utils {
        Int translateIndex(Int index, Int end) {
            if (index >= -end && index < end) {
                if (index < 0) {
                    return index + end;
                } else {
                    return index;
                }
            } else {
                throw IndexError(index, end);
            }
        }
    }
}