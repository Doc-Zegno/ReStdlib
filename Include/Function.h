#pragma once

#include "Any.h"


namespace ReLang {
    template<typename TResult, typename... TArgs>
    class Function : public Any {
    public:
		using FunctionType = Function<TResult, TArgs...>;

        virtual TResult operator()(TArgs... args) = 0;

		template<typename TOtherResult, typename... TOtherArgs>
		static Ptr<Function<TResult, TArgs...>> upcast(Ptr<Function<TOtherResult, TOtherArgs...>> function);
    };



	template<typename TFunction, typename... TArgs>
	auto makeFunc(TArgs&&... args) -> Ptr<typename TFunction::FunctionType> {
		return makePtr<TFunction>(std::forward<TArgs>(args)...);
	}



	template<typename TResult, typename ...TArgs>
	Ptr<Function<TResult, TArgs...>> box(TResult function(TArgs...)) {
		class Wrapper : public Function<TResult, TArgs...> {
		private:
			TResult(*_function)(TArgs...);

		public:
			Wrapper(TResult(*function)(TArgs...)) : _function(function) {}

			virtual TResult operator()(TArgs ...args) override {
				return _function(args...);
			}
		};


		return makeFunc<Wrapper>(function);
	}



	/*template<typename T>
	auto box(T t) -> typename std::enable_if<std::is_function<decltype(*t)>::value, decltype(boxFunction(t))>::type {
		return boxFunction(t);
	}*/



	template<typename TResult, typename ...TArgs>
	template<typename TOtherResult, typename ...TOtherArgs>
	inline Ptr<Function<TResult, TArgs...>> Function<TResult, TArgs...>::upcast(Ptr<Function<TOtherResult, TOtherArgs...>> function) {
		class Caster : public Function<TResult, TArgs...> {
		private:
			Ptr<Function<TOtherResult, TOtherArgs...>> _function;

		public:
			Caster(Ptr<Function<TOtherResult, TOtherArgs...>> function) : _function(function) {}

			virtual TResult operator()(TArgs ...args) override {
				auto result = _function(ReLang::upcast<TOtherArgs>(args)...);
				return ReLang::upcast<TOtherResult>(result);
			}
		};


		return makeFunc<Caster>(function);
	}
}
