#ifndef ANY_H
#define ANY_H

#include "Ptr.h"


namespace ReLang {
    class String;

    class Any {
    public:
        virtual Ptr<String> toString();

        virtual ~Any() { }
    };
}


#endif
