#pragma once

#include <vector>

#include "Iterator.h"
#include "Function.h"
#include "Primitives.h"
#include "SelfReferencing.h"


namespace ReLang {
    template<typename T>
    class Iterable;


    template<typename T>
    class IterableCommon : public Any, public SelfReferencing<Iterable<T>> {
    public:
        virtual Ptr<Iterator<T>> getIterator() = 0;

        template<typename R>
        Ptr<Iterable<R>> map(Ptr<Function<R, T>> mapping);

        virtual Ptr<Iterable<T>> filter(Ptr<Function<Bool, T>> predicate);

        virtual ~IterableCommon() { }
    };



    template<typename T>
    class Iterable : public IterableCommon<T> {

    };



    template<typename R, typename T>
    class MapIterable : public Iterable<R>, public EnableSelf<MapIterable<R, T>> {
    private:
        class MapIterator : public Iterator<R>/*, public EnableSelf<MapIterator>*/ {
        private:
            Ptr<Iterator<T>> _iterator;
            Ptr<Function<R, T>> _mapping;

        public:
            MapIterator(Ptr<Iterator<T>> iterator, Ptr<Function<R, T>> mapping);

            virtual R getCurrent() override;
            virtual bool moveNext() override;

            //virtual Ptr<Any> getSelf() override;
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
        class FilterIterator : public Iterator<T>/*, public EnableSelf<FilterIterator>*/ {
        private:
            Ptr<Iterator<T>> _iterator;
            Ptr<Function<Bool, T>> _predicate;

        public:
            FilterIterator(Ptr<Iterator<T>> iterator, Ptr<Function<Bool, T>> predicate);

            virtual T getCurrent() override;
            virtual bool moveNext() override;

            //virtual Ptr<Any> getSelf() override;
        };


        Ptr<Iterable<T>> _iterable;
        Ptr<Function<Bool, T>> _predicate;

    public:
        FilterIterable(Ptr<Iterable<T>> iterable, Ptr<Function<Bool, T>> predicate);

        virtual Ptr<Iterator<T>> getIterator() override;
        virtual Ptr<Iterable<T>> getSelf() override;
    };



    template<typename R, typename T>
    inline MapIterable<R, T>::MapIterable(Ptr<Iterable<T>> iterable, Ptr<Function<R, T>> mapping)
        : _iterable(iterable), _mapping(mapping) { }


    template<typename R, typename T>
    inline Ptr<Iterator<R>> MapIterable<R, T>::getIterator()
    {
        return Ptr<Iterator<R>>(new MapIterator(_iterable->getIterator(), _mapping));
    }


    template<typename R, typename T>
    inline Ptr<Iterable<R>> MapIterable<R, T>::getSelf()
    {
        return this->shared_from_this();
    }



    template<typename R, typename T>
    inline MapIterable<R, T>::MapIterator::MapIterator(Ptr<Iterator<T>> iterator, Ptr<Function<R, T>> mapping)
        : _iterator(iterator), _mapping(mapping) { }


    template<typename R, typename T>
    inline R MapIterable<R, T>::MapIterator::getCurrent()
    {
        return _mapping->__call__(_iterator->getCurrent());
    }


    template<typename R, typename T>
    inline bool MapIterable<R, T>::MapIterator::moveNext()
    {
        return _iterator->moveNext();
    }


    /*template<typename R, typename T>
    inline Ptr<Any> MapIterable<R, T>::MapIterator::getSelf()
    {
        // return this->shared_from_this();

    }*/



    template<typename T>
    template<typename R>
    inline Ptr<Iterable<R>> IterableCommon<T>::map(Ptr<Function<R, T>> mapping)
    {
        return Ptr<Iterable<R>>(
            new MapIterable<R, T>(this->getSelf(), mapping));
    }


    template<typename T>
    inline Ptr<Iterable<T>> IterableCommon<T>::filter(Ptr<Function<Bool, T>> predicate)
    {
        return Ptr<Iterable<T>>(
            new FilterIterable<T>(this->getSelf(), predicate));
    }



    template<typename T>
    inline FilterIterable<T>::FilterIterator::FilterIterator(Ptr<Iterator<T>> iterator, Ptr<Function<Bool, T>> predicate)
        : _iterator(iterator), _predicate(predicate)
    {
    }


    template<typename T>
    inline T FilterIterable<T>::FilterIterator::getCurrent()
    {
        return _iterator->getCurrent();
    }


    template<typename T>
    inline bool FilterIterable<T>::FilterIterator::moveNext()
    {
        while (true) {
            if (_iterator->moveNext()) {
                if (_predicate->__call__(_iterator->getCurrent())) {
                    return true;
                }
            } else {
                return false;
            }
        }
    }



    template<typename T>
    inline FilterIterable<T>::FilterIterable(Ptr<Iterable<T>> iterable, Ptr<Function<Bool, T>> predicate)
        : _iterable(iterable), _predicate(predicate)
    {
    }


    template<typename T>
    inline Ptr<Iterator<T>> FilterIterable<T>::getIterator()
    {
        return Ptr<Iterator<T>>(
            new FilterIterator(_iterable->getIterator(), _predicate));
    }


    template<typename T>
    inline Ptr<Iterable<T>> FilterIterable<T>::getSelf()
    {
        return this->shared_from_this();
    }
}
