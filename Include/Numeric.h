#pragma once

#include "Any.h"


namespace ReLang {
	template<typename T>
	class Numeric : public virtual Any {
	public:
		virtual Ptr<T> operator+(Ptr<T> other) = 0;
		virtual Ptr<T> operator-(Ptr<T> other) = 0;
		virtual Ptr<T> operator*(Ptr<T> other) = 0;
	};
}
