#ifndef ERROR_H
#define ERROR_H

#include "Any.h"


namespace ReLang {
    class Error : public Any {
    private:
        Ptr<String> _message;

    public:
        Error(Ptr<String> message);

        virtual Ptr<String> getMessage();

        virtual Ptr<String> toString() override;
    };
}


#endif
