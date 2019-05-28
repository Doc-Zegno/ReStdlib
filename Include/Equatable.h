#pragma once

#include "Any.h"


namespace ReLang {
    template<typename T>
	class Equatable : public virtual Any {
    public:
        virtual Bool operator==(Ptr<T> other) = 0;
		virtual Bool operator!=(Ptr<T> other);
    };



	template<typename T>
	inline Bool Equatable<T>::operator!=(Ptr<T> other) {
		return !(this->operator==(other));
	}
}
