#pragma once

#include "Equatable.h"


namespace ReLang {
	template<typename T>
	class Comparable : public Equatable<T> {
	public:
		virtual Bool operator>(Ptr<T> other) = 0;
		virtual Bool operator<(Ptr<T> other) = 0;
		virtual Bool operator>=(Ptr<T> other) = 0;
		virtual Bool operator<=(Ptr<T> other) = 0;

		virtual Int compareTo(Ptr<T> other) = 0;
	};
}
