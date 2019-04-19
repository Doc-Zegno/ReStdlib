#pragma once

#include <vector>
#include <type_traits>

#include "Tuple.h"
#include "Iterator.h"
#include "Function.h"
#include "Primitives.h"
#include "SelfReferencing.h"
#include "Errors.h"


namespace ReLang {
    template<typename T>
    class Iterable;


    template<typename T>
    class IterableCommon : public Any, public SelfReferencing<Iterable<T>> {
    public:
        virtual Ptr<Iterator<T>> getIterator() = 0;

        virtual T getFirst();
        virtual T getLast();
        virtual Ptr<Iterable<T>> getRest();
        virtual Bool getIsEmpty();
        virtual Int getLength();
        virtual Bool getHasLength();

        template<Int dummy = 0>
        Ptr<Iterable<Tuple<Int, T>>> enumerate();

        template<typename R>
        Ptr<Iterable<R>> map(Ptr<Function<R, T>> mapping);

        template<Int dummy = 0>
        Ptr<Iterable<T>> filter(Ptr<Function<Bool, T>> predicate);

        virtual void forEach(Ptr<Function<Void, T>> action);

        virtual T reduce(Ptr<Function<T, T, T>> reducer);

        virtual Ptr<Iterable<T>> take(Int number);

        virtual Ptr<Iterable<T>> skip(Int number);

        virtual Ptr<String> toString() override;
    };



    // Specializations
    template<typename T>
    class Iterable : public IterableCommon<T> {

    };


    namespace Iterables {
        template<typename R, typename T>
        class MapIterable : public Iterable<R>, public EnableSelf<MapIterable<R, T>> {
        private:
            class MapIterator : public Iterator<R> {
            private:
                Ptr<Iterator<T>> _iterator;
                Ptr<Function<R, T>> _mapping;

            public:
                MapIterator(Ptr<Iterator<T>> iterator, Ptr<Function<R, T>> mapping);

                virtual R getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<R>> clone() override;
            };


            Ptr<Iterable<T>> _iterable;
            Ptr<Function<R, T>> _mapping;

        public:
            MapIterable(Ptr<Iterable<T>> iterable, Ptr<Function<R, T>> mapping);

            virtual Ptr<Iterator<R>> getIterator() override;
            virtual Ptr<Iterable<R>> getSelf() override;
        };



        template<typename T>
        class FilterIterable : public Iterable<T>, public EnableSelf<FilterIterable<T>> {
        private:
            class FilterIterator : public Iterator<T> {
            private:
                Ptr<Iterator<T>> _iterator;
                Ptr<Function<Bool, T>> _predicate;

            public:
                FilterIterator(Ptr<Iterator<T>> iterator, Ptr<Function<Bool, T>> predicate);

                virtual T getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<T>> clone() override;
            };


            Ptr<Iterable<T>> _iterable;
            Ptr<Function<Bool, T>> _predicate;

        public:
            FilterIterable(Ptr<Iterable<T>> iterable, Ptr<Function<Bool, T>> predicate);

            virtual Ptr<Iterator<T>> getIterator() override;
            virtual Ptr<Iterable<T>> getSelf() override;
        };



        template<typename T>
        class WrappingIterable : public Iterable<T>, public EnableSelf<WrappingIterable<T>> {
        private:
            Ptr<Iterator<T>> _iterator;

        public:
            WrappingIterable(Ptr<Iterator<T>> iterator);

            virtual Ptr<Iterator<T>> getIterator() override;
            virtual Ptr<Iterable<T>> getSelf() override;
        };



        template<typename T>
        class TakingIterable : public Iterable<T>, public EnableSelf<TakingIterable<T>> {
        private:
            class TakingIterator : public Iterator<T> {
            private:
                Ptr<Iterator<T>> _iterator;
                Int _number;
                Int _index;

            public:
                TakingIterator(Ptr<Iterator<T>> iterator, Int number, Int index = -1);

                virtual T getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<T>> clone() override;
            };


            Ptr<Iterable<T>> _iterable;
            Int _number;

        public:
            TakingIterable(Ptr<Iterable<T>> iterable, Int number);

            virtual Ptr<Iterator<T>> getIterator() override;
            virtual Ptr<Iterable<T>> getSelf() override;
        };



        template<typename T>
        class EnumeratingIterable : public Iterable<Tuple<Int, T>>, public EnableSelf<EnumeratingIterable<T>> {
        private:
            class EnumeratingIterator : public Iterator<Tuple<Int, T>> {
            private:
                Ptr<Iterator<T>> _iterator;
                Int _index;

            public:
                EnumeratingIterator(Ptr<Iterator<T>> iterator, Int index = -1);

                virtual Tuple<Int, T> getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<Tuple<Int, T>>> clone() override;
            };


            Ptr<Iterable<T>> _iterable;

        public:
            EnumeratingIterable(Ptr<Iterable<T>> iterable);

            virtual Ptr<Iterator<Tuple<Int, T>>> getIterator() override;
            virtual Ptr<Iterable<Tuple<Int, T>>> getSelf() override;
        };



        template<typename U, typename V>
        class ZippingIterable : public Iterable<Tuple<U, V>>, public EnableSelf<ZippingIterable<U, V>> {
        private:
            class ZippingIterator : public Iterator<Tuple<U, V>> {
            private:
                Ptr<Iterator<U>> _uIterator;
                Ptr<Iterator<V>> _vIterator;

            public:
                ZippingIterator(Ptr<Iterator<U>> uIterator, Ptr<Iterator<V>> vIterator);

                virtual Tuple<U, V> getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<Tuple<U, V>>> clone() override;
            };


            Ptr<Iterable<U>> _us;
            Ptr<Iterable<V>> _vs;

        public:
            ZippingIterable(Ptr<Iterable<U>> us, Ptr<Iterable<V>> vs);

            virtual Ptr<Iterator<Tuple<U, V>>> getIterator() override;
            virtual Ptr<Iterable<Tuple<U, V>>> getSelf() override;
        };



        // M a p I t e r a b l e
        template<typename R, typename T>
        inline MapIterable<R, T>::MapIterable(Ptr<Iterable<T>> iterable, Ptr<Function<R, T>> mapping)
            : _iterable(iterable), _mapping(mapping) {
        }


        template<typename R, typename T>
        inline Ptr<Iterator<R>> MapIterable<R, T>::getIterator() {
            return Ptr<Iterator<R>>(new MapIterator(_iterable->getIterator(), _mapping));
        }


        template<typename R, typename T>
        inline Ptr<Iterable<R>> MapIterable<R, T>::getSelf() {
            return this->shared_from_this();
        }



        // M a p I t e r a t o r
        template<typename R, typename T>
        inline MapIterable<R, T>::MapIterator::MapIterator(Ptr<Iterator<T>> iterator, Ptr<Function<R, T>> mapping)
            : _iterator(iterator), _mapping(mapping) {
        }


        template<typename R, typename T>
        inline R MapIterable<R, T>::MapIterator::getCurrent() {
            return _mapping->operator()(_iterator->getCurrent());
        }


        template<typename R, typename T>
        inline Bool MapIterable<R, T>::MapIterator::moveNext() {
            return _iterator->moveNext();
        }


        template<typename R, typename T>
        inline Ptr<Iterator<R>> MapIterable<R, T>::MapIterator::clone() {
            return Ptr<Iterator<R>>(new MapIterator(_iterator->clone(), _mapping));
        }



        // F i l t e r I t e r a t o r
        template<typename T>
        inline FilterIterable<T>::FilterIterator::FilterIterator(Ptr<Iterator<T>> iterator, Ptr<Function<Bool, T>> predicate)
            : _iterator(iterator), _predicate(predicate) {
        }


        template<typename T>
        inline T FilterIterable<T>::FilterIterator::getCurrent() {
            return _iterator->getCurrent();
        }


        template<typename T>
        inline Bool FilterIterable<T>::FilterIterator::moveNext() {
            while (true) {
                if (_iterator->moveNext()) {
                    if (_predicate->operator()(_iterator->getCurrent())) {
                        return true;
                    }
                } else {
                    return false;
                }
            }
        }


        template<typename T>
        inline Ptr<Iterator<T>> FilterIterable<T>::FilterIterator::clone() {
            return Ptr<Iterator<T>>(new FilterIterator(_iterator->clone(), _predicate));
        }



        // F i l t e r I t e r a b l e
        template<typename T>
        inline FilterIterable<T>::FilterIterable(Ptr<Iterable<T>> iterable, Ptr<Function<Bool, T>> predicate)
            : _iterable(iterable), _predicate(predicate) {
        }


        template<typename T>
        inline Ptr<Iterator<T>> FilterIterable<T>::getIterator() {
            return Ptr<Iterator<T>>(
                new FilterIterator(_iterable->getIterator(), _predicate));
        }


        template<typename T>
        inline Ptr<Iterable<T>> FilterIterable<T>::getSelf() {
            return this->shared_from_this();
        }



        // W r a p p i n g I t e r a b l e
        template<typename T>
        inline WrappingIterable<T>::WrappingIterable(Ptr<Iterator<T>> iterator) : _iterator(iterator) {
        }


        template<typename T>
        inline Ptr<Iterator<T>> WrappingIterable<T>::getIterator() {
            return _iterator->clone();
        }


        template<typename T>
        inline Ptr<Iterable<T>> WrappingIterable<T>::getSelf() {
            return this->shared_from_this();
        }



        // T a k i n g I t e r a b l e
        template<typename T>
        inline TakingIterable<T>::TakingIterable(Ptr<Iterable<T>> iterable, Int number) : _iterable(iterable), _number(number) {
        }


        template<typename T>
        inline Ptr<Iterator<T>> TakingIterable<T>::getIterator() {
            return Ptr<Iterator<T>>(new TakingIterator(_iterable->getIterator(), _number));
        }


        template<typename T>
        inline Ptr<Iterable<T>> TakingIterable<T>::getSelf() {
            return this->shared_from_this();
        }



        // T a k i n g I t e r a t o r
        template<typename T>
        inline TakingIterable<T>::TakingIterator::TakingIterator(Ptr<Iterator<T>> iterator, Int number, Int index)
            : _iterator(iterator), _number(number), _index(index)
        {
        }


        template<typename T>
        inline T TakingIterable<T>::TakingIterator::getCurrent() {
            if (_index >= 0 && _index < _number) {
                return _iterator->getCurrent();
            } else {
                throw InvalidIteratorError();
            }
        }


        template<typename T>
        inline Bool TakingIterable<T>::TakingIterator::moveNext() {
            _index++;
            if (_index < _number) {
                return _iterator->moveNext();
            } else {
                _index = _number;
                return false;
            }
        }


        template<typename T>
        inline Ptr<Iterator<T>> TakingIterable<T>::TakingIterator::clone() {
            return Ptr<Iterator<T>>(new TakingIterator(_iterator->clone(), _number, _index));
        }



        // E n u m e r a t i n g I t e r a b l e
        template<typename T>
        inline EnumeratingIterable<T>::EnumeratingIterable(Ptr<Iterable<T>> iterable) : _iterable(iterable) {
        }


        template<typename T>
        inline Ptr<Iterator<Tuple<Int, T>>> EnumeratingIterable<T>::getIterator() {
            return Ptr<Iterator<Tuple<Int, T>>>(new EnumeratingIterator(_iterable->getIterator()));
        }


        template<typename T>
        inline Ptr<Iterable<Tuple<Int, T>>> EnumeratingIterable<T>::getSelf() {
            return this->shared_from_this();
        }



        // E n u m e r a t i n g I t e r a t o r
        template<typename T>
        inline EnumeratingIterable<T>::EnumeratingIterator::EnumeratingIterator(Ptr<Iterator<T>> iterator, Int index)
            : _iterator(iterator), _index(index)
        {
        }


        template<typename T>
        inline Tuple<Int, T> EnumeratingIterable<T>::EnumeratingIterator::getCurrent() {
            return Tuple<Int, T>(_index, _iterator->getCurrent());
        }


        template<typename T>
        inline Bool EnumeratingIterable<T>::EnumeratingIterator::moveNext() {
            if (_iterator->moveNext()) {
                _index++;
                return true;
            } else {
                return false;
            }
        }


        template<typename T>
        inline Ptr<Iterator<Tuple<Int, T>>> EnumeratingIterable<T>::EnumeratingIterator::clone() {
            return Ptr<Iterator<Tuple<Int, T>>>(new EnumeratingIterator(_iterator->clone(), _index));
        }



        // Z i p p i n g I t e r a b l e
        template<typename U, typename V>
        inline ZippingIterable<U, V>::ZippingIterable(Ptr<Iterable<U>> us, Ptr<Iterable<V>> vs)
            : _us(us), _vs(vs)
        {
        }


        template<typename U, typename V>
        inline Ptr<Iterator<Tuple<U, V>>> ZippingIterable<U, V>::getIterator() {
            return Ptr<Iterator<Tuple<U, V>>>(new ZippingIterator(_us->getIterator(), _vs->getIterator()));
        }


        template<typename U, typename V>
        inline Ptr<Iterable<Tuple<U, V>>> ZippingIterable<U, V>::getSelf() {
            return this->shared_from_this();
        }



        // Z i p p i n g I t e r a t o r
        template<typename U, typename V>
        inline ZippingIterable<U, V>::ZippingIterator::ZippingIterator(Ptr<Iterator<U>> uIterator, Ptr<Iterator<V>> vIterator)
            : _uIterator(uIterator), _vIterator(vIterator)
        {
        }


        template<typename U, typename V>
        inline Tuple<U, V> ZippingIterable<U, V>::ZippingIterator::getCurrent() {
            return Tuple<U, V>(_uIterator->getCurrent(), _vIterator->getCurrent());
        }


        template<typename U, typename V>
        inline Bool ZippingIterable<U, V>::ZippingIterator::moveNext() {
            return _uIterator->moveNext() && _vIterator->moveNext();
        }


        template<typename U, typename V>
        inline Ptr<Iterator<Tuple<U, V>>> ZippingIterable<U, V>::ZippingIterator::clone() {
            return Ptr<Iterator<Tuple<U, V>>>(new ZippingIterator(_uIterator->clone(), _vIterator->clone()));
        }
    }



    // I t e r a b l e C o m m o n
    template<typename T>
    template<Int dummy>
    inline Ptr<Iterable<Tuple<Int, T>>> IterableCommon<T>::enumerate() {
        return Ptr<Iterable<Tuple<Int, T>>>(new Iterables::EnumeratingIterable<T>(this->getSelf()));
    }


    template<typename T>
    template<typename R>
    inline Ptr<Iterable<R>> IterableCommon<T>::map(Ptr<Function<R, T>> mapping) {
        return Ptr<Iterable<R>>(
            new Iterables::MapIterable<R, T>(this->getSelf(), mapping));
    }


    template<typename T>
    template<Int dummy>
    inline Ptr<Iterable<T>> IterableCommon<T>::filter(Ptr<Function<Bool, T>> predicate) {
        return Ptr<Iterable<T>>(
            new Iterables::FilterIterable<T>(this->getSelf(), predicate));
    }


    template<typename T>
    inline void IterableCommon<T>::forEach(Ptr<Function<Void, T>> action) {
        auto iterator = getIterator();
        while (iterator->moveNext()) {
            (*action)(iterator->getCurrent());
        }
    }


    template<typename T>
    inline T IterableCommon<T>::reduce(Ptr<Function<T, T, T>> reducer) {
        auto iterator = getIterator();
        if (iterator->moveNext()) {
            auto accumulator = iterator->getCurrent();
            while (iterator->moveNext()) {
                accumulator = (*reducer)(accumulator, iterator->getCurrent());
            }
            return accumulator;
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline Ptr<Iterable<T>> IterableCommon<T>::take(Int number) {
        return Ptr<Iterable<T>>(new Iterables::TakingIterable<T>(this->getSelf(), number));
    }


    template<typename T>
    inline Ptr<Iterable<T>> IterableCommon<T>::skip(Int number) {
        auto iterator = getIterator();
        for (auto i = 0; i < number && iterator->moveNext(); i++) {
        }
        return Ptr<Iterable<T>>(new Iterables::WrappingIterable<T>(iterator));
    }


    template<typename T>
    inline T IterableCommon<T>::getFirst() {
        auto iterator = getIterator();
        if (iterator->moveNext()) {
            return iterator->getCurrent();
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline T IterableCommon<T>::getLast() {
        auto iterator = getIterator();
        if (iterator->moveNext()) {
            while (true) {
                auto current = iterator->getCurrent();
                if (!iterator->moveNext()) {
                    return current;
                }
            }
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline Ptr<Iterable<T>> IterableCommon<T>::getRest() {
        auto iterator = getIterator();
        if (iterator->moveNext()) {
            return Ptr<Iterable<T>>(new Iterables::WrappingIterable<T>(iterator));
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline Bool IterableCommon<T>::getIsEmpty() {
        auto iterator = getIterator();
        return !iterator->moveNext();
    }


    template<typename T>
    inline Int IterableCommon<T>::getLength() {
        throw NotImplementedError();
    }


    template<typename T>
    inline Bool IterableCommon<T>::getHasLength() {
        return false;
    }



    // Global functions
    template<typename Us, typename Vs>
    auto zip(Ptr<Us> us, Ptr<Vs> vs) -> Ptr<Iterable<Tuple<decltype(us->getIterator()->getCurrent()), decltype(vs->getIterator()->getCurrent())>>> {
        using U = decltype(us->getIterator()->getCurrent());
        using V = decltype(vs->getIterator()->getCurrent());

        auto uIterable = Ptr<Iterable<U>>(us);
        auto vIterable = Ptr<Iterable<V>>(vs);
        return Ptr<Iterable<Tuple<U, V>>>(new Iterables::ZippingIterable<U, V>(uIterable, vIterable));
    }
}


// Specializations
#include "Utils/StringUtils.h"


namespace ReLang {    
    template<typename T>
    inline Ptr<String> IterableCommon<T>::toString() {
        return Utils::join(L"::", this->getSelf(), L"", L"::[]");
    }
}
