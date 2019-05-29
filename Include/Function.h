#pragma once

#include "Any.h"


namespace ReLang {
    template<typename TResult, typename... TArgs>
    class Function : public Any {
    public:
		using FunctionType = Function<TResult, TArgs...>;

        virtual TResult operator()(TArgs... args) = 0;
    };



	template<typename TFunction, typename... TArgs>
	auto makeFunc(TArgs&&... args) -> Ptr<typename TFunction::FunctionType> {
		return makePtr<TFunction>(std::forward<TArgs>(args)...);
	}
}
