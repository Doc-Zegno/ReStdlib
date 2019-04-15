#ifndef SELF_REFERENCING_H
#define SELF_REFERENCING_H

#include "Ptr.h"


namespace ReLang {
    template<typename T>
    class SelfReferencing {
    public:
        virtual Ptr<T> getSelf() = 0;

        virtual ~SelfReferencing() {}
    };


    template<typename T>
    using EnableSelf = std::enable_shared_from_this<T>;
}


#endif