#pragma once

#include "Primitives.h"
#include "Function.h"


namespace ReLang {
    namespace Utils {
        template<typename T>
        class AscendingComparator : public Function<Bool, T, T> {
        public:
            virtual Bool operator()(T t1, T t2) override {
                return t1 <= t2;
            }
        };



        template<typename T>
        class DescendingComparator : public Function<Bool, T, T> {
        public:
            virtual Bool operator()(T t1, T t2) override {
                return t1 >= t2;
            }
        };



        template<typename K, typename T>
        class AscendingKeyComparator : public Function<Bool, T, T> {
        private:
            Ptr<Function<K, T>> _key;

        public:
            AscendingKeyComparator(Ptr<Function<K, T>> key) : _key(key) {}

            virtual Bool operator()(T t1, T t2) override {
                auto k1 = (*_key)(t1);
                auto k2 = (*_key)(t2);
                return k1 <= k2;
            }
        };



        template<typename K, typename T>
        class DescendingKeyComparator : public Function<Bool, T, T> {
        private:
            Ptr<Function<K, T>> _key;

        public:
            DescendingKeyComparator(Ptr<Function<K, T>> key) : _key(key) {}

            virtual Bool operator()(T t1, T t2) override {
                auto k1 = (*_key)(t1);
                auto k2 = (*_key)(t2);
                return k1 >= k2;
            }
        };
    }
}