#pragma once

#include <iostream>
#include <initializer_list>
#include <memory>


namespace ReLang {
    template<typename T>
    using Ptr = std::shared_ptr<T>;


    template<typename T>
    using WeakPtr = std::shared_ptr<T>;


    template<typename TObject, typename ...TArgs>
    inline Ptr<TObject> makePtr(TArgs&& ...args) {
        return Ptr<TObject>(new TObject(std::forward<TArgs>(args)...));
    }


    template<typename TObject, typename TArg>
    inline Ptr<TObject> makePtr(std::initializer_list<TArg> args) {
        return Ptr<TObject>(new TObject(args));
    }
}
