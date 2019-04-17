#pragma once

#include <memory>


namespace ReLang {
    template<typename T>
    using Ptr = std::shared_ptr<T>;

    template<typename T>
    using WeakPtr = std::shared_ptr<T>;
}
