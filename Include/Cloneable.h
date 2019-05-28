#pragma once


namespace ReLang {
    template<typename T>
    class Cloneable : public virtual Any {
    public:
        virtual Ptr<T> clone() = 0;
    };
}
