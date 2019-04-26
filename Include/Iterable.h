#pragma once

#include <vector>
#include <algorithm>
#include <type_traits>

#include "Tuple.h"
#include "Iterator.h"
#include "Function.h"
#include "Primitives.h"
#include "SelfReferencing.h"
#include "Errors.h"

#include "Utils/FunctionUtils.h"


namespace ReLang {
    template<typename T>
    class Iterable;


    template<typename T>
    class IterableCommon : public Any, public SelfReferencing<Iterable<T>> {
    private:
        Tuple<T, Int> supremeWith(Ptr<Function<Bool, T, T>> comparator);

    public:
        virtual Ptr<Iterator<T>> getIterator() = 0;

        virtual T getFirst();

        virtual T getLast();

        virtual Ptr<Iterable<T>> getRest();

        virtual Bool getIsEmpty();

        virtual Int getLength();

        virtual Bool getHasLength();

        virtual Ptr<Iterable<Int>> getIndices();

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

        template<Int dummy = 0>
        Ptr<Iterable<T>> sort(Bool isAscending = Bool(true));

        template<typename K>
        Ptr<Iterable<T>> sortBy(Ptr<Function<K, T>> key, Bool isAscending = Bool(true));

        virtual Ptr<Iterable<T>> sortWith(Ptr<Function<Bool, T, T>> comparator);

        template<typename K>
        Tuple<T, Int> maxBy(Ptr<Function<K, T>> key);

        template<typename K>
        Tuple<T, Int> minBy(Ptr<Function<K, T>> key);

        template<Int dummy = 0>
        Tuple<T, Int> max();

        template<Int dummy = 0>
        Tuple<T, Int> min();

        virtual Ptr<Iterable<T>> cons(T value);

        template<typename R>
        Ptr<Iterable<R>> flatten();

        template<typename R, typename Rs>
        Ptr<Iterable<R>> flatMap(Ptr<Function<Rs, T>> mapping);

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
            virtual Bool getHasLength() override;
            virtual Int getLength() override;
            virtual Bool getIsEmpty() override;
            virtual Ptr<Iterable<R>> getSelf() override;
        };



        template<typename T>
        class FilterIterable : public Iterable<T>, public EnableSelf<FilterIterable<T>> {
        private:
            class FilterIterator : public Iterator<T> {
            private:
                Ptr<Iterator<T>> _iterator;
                Ptr<Function<Bool, T>> _predicate;
                T _current;

            public:
                FilterIterator(Ptr<Iterator<T>> iterator, Ptr<Function<Bool, T>> predicate, T current = T());

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
            virtual Bool getHasLength() override;
            virtual Int getLength() override;
            virtual Bool getIsEmpty() override;
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
            virtual Bool getHasLength() override;
            virtual Int getLength() override;
            virtual Bool getIsEmpty() override;
            virtual Ptr<Iterable<Tuple<U, V>>> getSelf() override;
        };



        template<typename T>
        class IndexingIterable : public Iterable<Int>, public EnableSelf<IndexingIterable<T>> {
        private:
            class IndexingIterator : public Iterator<Int> {
            private:
                Ptr<Iterator<T>> _iterator;
                Int _index;

            public:
                IndexingIterator(Ptr<Iterator<T>> iterator, Int index = -1);

                virtual Int getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<Int>> clone() override;
            };


            Ptr<Iterable<T>> _iterable;

        public:
            IndexingIterable(Ptr<Iterable<T>> iterable);

            virtual Ptr<Iterator<Int>> getIterator() override;
            virtual Bool getHasLength() override;
            virtual Int getLength() override;
            virtual Bool getIsEmpty() override;
            virtual Ptr<Iterable<Int>> getSelf() override;
        };



        template<typename T>
        struct ConstructingNode {
            T value;
            Ptr<ConstructingNode<T>> next;

            ConstructingNode(T value, Ptr<ConstructingNode<T>> next = Ptr<ConstructingNode<T>>()) : value(value), next(next) {}
        };



        template<typename T>
        class ConstructingIterable : public Iterable<T>, public EnableSelf<ConstructingIterable<T>> {
        private:
            class ConstructingIterator : public Iterator<T> {
            private:
                Ptr<ConstructingNode<T>> _first;
                Ptr<Iterator<T>> _rest;
                Bool _isValid;

            public:
                ConstructingIterator(Ptr<ConstructingNode<T>> first, Ptr<Iterator<T>> rest, Bool isValid);

                virtual T getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<T>> clone() override;
            };


            Ptr<ConstructingNode<T>> _first;
            Ptr<Iterable<T>> _rest;
            Int _listLength;

        public:
            ConstructingIterable(Ptr<ConstructingNode<T>> first, Ptr<Iterable<T>> rest, Int listLength);

            virtual Ptr<Iterator<T>> getIterator() override;
            virtual Bool getHasLength() override;
            virtual Int getLength() override;
            virtual Bool getIsEmpty() override;
            virtual Ptr<Iterable<T>> getSelf() override;
            virtual Ptr<Iterable<T>> cons(T value) override;
        };



        template<typename T>
        class VectorIterable : public Iterable<T>, public EnableSelf<VectorIterable<T>> {
        private:
            class VectorIterator : public Iterator<T> {
            private:
                Ptr<VectorIterable<T>> _iterable;
                Int _index;
                Int _length;

            public:
                VectorIterator(Ptr<VectorIterable<T>> iterable, Int index, Int length);

                virtual T getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<T>> clone() override;
            };


            std::vector<T> _vector;

        public:
            VectorIterable(std::vector<T>&& vector);

            virtual Ptr<Iterator<T>> getIterator() override;
            virtual Bool getHasLength() override;
            virtual Int getLength() override;
            virtual Bool getIsEmpty() override;
            virtual Ptr<Iterable<T>> getSelf() override;

            T operator[](Int index);
        };



        template<typename T, typename R>
        class FlatteningIterable : public Iterable<R>, public EnableSelf<FlatteningIterable<T, R>> {
        private:
            class FlatteningIterator : public Iterator<R> {
            private:
                Ptr<Iterator<T>> _outerIterator;
                Ptr<Iterator<R>> _innerIterator;

            public:
                FlatteningIterator(Ptr<Iterator<T>> outerIterator, Ptr<Iterator<R>> innerIterator);

                virtual R getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<R>> clone() override;
            };


            Ptr<Iterable<T>> _iterable;
        public:
            FlatteningIterable(Ptr<Iterable<T>> iterable);

            virtual Ptr<Iterator<R>> getIterator() override;
            virtual Ptr<Iterable<R>> getSelf() override;
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
        inline Bool MapIterable<R, T>::getHasLength() {
            return _iterable->getHasLength();
        }


        template<typename R, typename T>
        inline Int MapIterable<R, T>::getLength() {
            return _iterable->getLength();
        }


        template<typename R, typename T>
        inline Bool MapIterable<R, T>::getIsEmpty() {
            return _iterable->getIsEmpty();
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
        inline FilterIterable<T>::FilterIterator::FilterIterator(Ptr<Iterator<T>> iterator, Ptr<Function<Bool, T>> predicate, T current)
            : _iterator(iterator), _predicate(predicate), _current(current) {
        }


        template<typename T>
        inline T FilterIterable<T>::FilterIterator::getCurrent() {
            return _current;
        }


        template<typename T>
        inline Bool FilterIterable<T>::FilterIterator::moveNext() {
            while (true) {
                if (_iterator->moveNext()) {
                    _current = _iterator->getCurrent();
                    if ((*_predicate)(_current)) {
                        return true;
                    }
                } else {
                    return false;
                }
            }
        }


        template<typename T>
        inline Ptr<Iterator<T>> FilterIterable<T>::FilterIterator::clone() {
            return Ptr<Iterator<T>>(new FilterIterator(_iterator->clone(), _predicate, _current));
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
        inline Bool EnumeratingIterable<T>::getHasLength() {
            return _iterable->getHasLength();
        }


        template<typename T>
        inline Int EnumeratingIterable<T>::getLength() {
            return _iterable->getLength();
        }


        template<typename T>
        inline Bool EnumeratingIterable<T>::getIsEmpty() {
            return _iterable->getIsEmpty();
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
        inline Bool ZippingIterable<U, V>::getHasLength() {
            return _us->getHasLength() && _vs->getHasLength();
        }


        template<typename U, typename V>
        inline Int ZippingIterable<U, V>::getLength() {
            return std::min(_us->getLength(), _vs->getLength());
        }


        template<typename U, typename V>
        inline Bool ZippingIterable<U, V>::getIsEmpty() {
            return _us->getIsEmpty() || _vs->getIsEmpty();
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



        // I n d e x i n g I t e r a b l e
        template<typename T>
        inline IndexingIterable<T>::IndexingIterable(Ptr<Iterable<T>> iterable) : _iterable(iterable) {
        }


        template<typename T>
        inline Ptr<Iterator<Int>> IndexingIterable<T>::getIterator() {
            return Ptr<Iterator<Int>>(new IndexingIterator(_iterable->getIterator()));
        }


        template<typename T>
        inline Bool IndexingIterable<T>::getHasLength() {
            return _iterable->getHasLength();
        }


        template<typename T>
        inline Int IndexingIterable<T>::getLength() {
            return _iterable->getLength();
        }


        template<typename T>
        inline Bool IndexingIterable<T>::getIsEmpty() {
            return _iterable->getIsEmpty();
        }


        template<typename T>
        inline Ptr<Iterable<Int>> IndexingIterable<T>::getSelf() {
            return this->shared_from_this();
        }



        // I n d e x i n g I t e r a t o r
        template<typename T>
        inline IndexingIterable<T>::IndexingIterator::IndexingIterator(Ptr<Iterator<T>> iterator, Int index)
            : _iterator(iterator), _index(index)
        {
        }


        template<typename T>
        inline Int IndexingIterable<T>::IndexingIterator::getCurrent() {
            if (_index >= 0) {
                return _index;
            } else {
                throw InvalidIteratorError();
            }
        }


        template<typename T>
        inline Bool IndexingIterable<T>::IndexingIterator::moveNext() {
            auto moved = _iterator->moveNext();
            if (moved) {
                _index++;
                return true;
            } else {
                return false;
            }
        }


        template<typename T>
        inline Ptr<Iterator<Int>> IndexingIterable<T>::IndexingIterator::clone() {
            return Ptr<Iterator<Int>>(new IndexingIterator(_iterator->clone(), _index));
        }



        // C o n s t r u c t i n g I t e r a b l e
        template<typename T>
        inline ConstructingIterable<T>::ConstructingIterable(Ptr<ConstructingNode<T>> first, Ptr<Iterable<T>> rest, Int listLength)
            : _first(first), _rest(rest), _listLength(listLength)
        {
        }


        template<typename T>
        inline Ptr<Iterator<T>> ConstructingIterable<T>::getIterator() {
            return Ptr<Iterator<T>>(new ConstructingIterator(_first, _rest->getIterator(), false));
        }


        template<typename T>
        inline Bool ConstructingIterable<T>::getHasLength() {
            return _rest->getHasLength();
        }


        template<typename T>
        inline Int ConstructingIterable<T>::getLength() {
            return _listLength + _rest->getLength();
        }


        template<typename T>
        inline Bool ConstructingIterable<T>::getIsEmpty() {
            return Bool(false);  // Always has at least one element
        }


        template<typename T>
        inline Ptr<Iterable<T>> ConstructingIterable<T>::getSelf() {
            return this->shared_from_this();
        }


        template<typename T>
        inline Ptr<Iterable<T>> ConstructingIterable<T>::cons(T value) {
            auto node = makePtr<ConstructingNode<T>>(value, _first);
            return Ptr<Iterable<T>>(new ConstructingIterable<T>(node, _rest, _listLength + 1));
        }



        // C o n s t r u c t i n g I t e r a t o r
        template<typename T>
        inline ConstructingIterable<T>::ConstructingIterator::ConstructingIterator(Ptr<ConstructingNode<T>> first, Ptr<Iterator<T>> rest, Bool isValid)
            : _first(first), _rest(rest), _isValid(isValid)
        {
        }


        template<typename T>
        inline T ConstructingIterable<T>::ConstructingIterator::getCurrent() {
            if (_isValid) {
                if (_first) {
                    return _first->value;
                } else {
                    return _rest->getCurrent();
                }
            } else {
                throw InvalidIteratorError();
            }
        }


        template<typename T>
        inline Bool ConstructingIterable<T>::ConstructingIterator::moveNext() {
            if (!_isValid) {
                // Already pointing at element
                _isValid = true;
                return true;
            } else {
                if (_first) {
                    _first = _first->next;
                    if (_first) {
                        return true;
                    } else {
                        return _rest->moveNext();
                    }
                } else {
                    return _rest->moveNext();
                }
            }
        }


        template<typename T>
        inline Ptr<Iterator<T>> ConstructingIterable<T>::ConstructingIterator::clone() {
            return Ptr<Iterator<T>>(new ConstructingIterator(_first, _rest->clone(), _isValid));
        }



        // V e c t o r I t e r a b l e
        template<typename T>
        inline VectorIterable<T>::VectorIterable(std::vector<T>&& vector) : _vector(std::move(vector)) {
        }


        template<typename T>
        inline Ptr<Iterator<T>> VectorIterable<T>::getIterator() {
            auto length = Int(_vector.size());
            return Ptr<Iterator<T>>(new VectorIterator(this->shared_from_this(), -1, length));
        }


        template<typename T>
        inline Bool VectorIterable<T>::getHasLength() {
            return true;
        }


        template<typename T>
        inline Int VectorIterable<T>::getLength() {
            return Int(_vector.size());
        }


        template<typename T>
        inline Bool VectorIterable<T>::getIsEmpty() {
            return _vector.empty();
        }


        template<typename T>
        inline Ptr<Iterable<T>> VectorIterable<T>::getSelf() {
            return this->shared_from_this();
        }


        template<typename T>
        inline T VectorIterable<T>::operator[](Int index) {
            return _vector[index];
        }



        // V e c t o r I t e r a t o r
        template<typename T>
        inline VectorIterable<T>::VectorIterator::VectorIterator(Ptr<VectorIterable<T>> iterable, Int index, Int length)
            : _iterable(iterable), _index(index), _length(length)
        {
        }


        template<typename T>
        inline T VectorIterable<T>::VectorIterator::getCurrent() {
            if (_index >= 0 && _index < _length) {
                return (*_iterable)[_index];
            } else {
                throw InvalidIteratorError();
            }
        }


        template<typename T>
        inline Bool VectorIterable<T>::VectorIterator::moveNext() {
            _index++;
            if (_index >= _length) {
                _index = _length;
                return false;
            } else {
                return true;
            }
        }


        template<typename T>
        inline Ptr<Iterator<T>> VectorIterable<T>::VectorIterator::clone() {
            return Ptr<Iterator<T>>(new VectorIterator(_iterable, _index, _length));
        }



        // F l a t t e n i n g I t e r a b l e
        template<typename T, typename R>
        inline FlatteningIterable<T, R>::FlatteningIterable(Ptr<Iterable<T>> iterable) : _iterable(iterable) {
        }


        template<typename T, typename R>
        inline Ptr<Iterator<R>> FlatteningIterable<T, R>::getIterator() {
            return Ptr<Iterator<R>>(new FlatteningIterator(_iterable->getIterator(), Ptr<Iterator<R>>()));
        }


        template<typename T, typename R>
        inline Ptr<Iterable<R>> FlatteningIterable<T, R>::getSelf() {
            return this->shared_from_this();
        }



        // F l a t t e n i n g I t e r a t o r
        template<typename T, typename R>
        inline FlatteningIterable<T, R>::FlatteningIterator::FlatteningIterator(Ptr<Iterator<T>> outerIterator, Ptr<Iterator<R>> innerIterator)
            : _outerIterator(outerIterator), _innerIterator(innerIterator)
        {
        }


        template<typename T, typename R>
        inline R FlatteningIterable<T, R>::FlatteningIterator::getCurrent() {
            if (_innerIterator) {
                return _innerIterator->getCurrent();
            } else {
                throw InvalidIteratorError();
            }
        }


        template<typename T, typename R>
        inline Bool FlatteningIterable<T, R>::FlatteningIterator::moveNext() {
            if (_innerIterator) {
                if (_innerIterator->moveNext()) {
                    return true;
                } else {
                    _innerIterator = Ptr<Iterator<R>>();
                    return FlatteningIterator::moveNext();
                }
            } else {
                // First move
                if (_outerIterator->moveNext()) {
                    _innerIterator = _outerIterator->getCurrent()->getIterator();
                    return FlatteningIterator::moveNext();
                } else {
                    return false;
                }
            }
        }


        template<typename T, typename R>
        inline Ptr<Iterator<R>> FlatteningIterable<T, R>::FlatteningIterator::clone() {
            auto outerClone = _outerIterator->clone();
            auto innerClone = _innerIterator ? _innerIterator->clone() : Ptr<Iterator<R>>();
            return Ptr<Iterator<R>>(new FlatteningIterator(outerClone, innerClone));
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
    template<Int dummy>
    inline Ptr<Iterable<T>> IterableCommon<T>::sort(Bool isAscending) {
        if (isAscending) {
            return sortWith(Ptr<Function<Bool, T, T>>(new Utils::AscendingComparator<T>()));
        } else {
            return sortWith(Ptr<Function<Bool, T, T>>(new Utils::DescendingComparator<T>()));
        }
    }


    template<typename T>
    template<typename K>
    inline Ptr<Iterable<T>> IterableCommon<T>::sortBy(Ptr<Function<K, T>> key, Bool isAscending) {
        if (isAscending) {
            return sortWith(Ptr<Function<Bool, T, T>>(new Utils::AscendingKeyComparator<K, T>(key)));
        } else {
            return sortWith(Ptr<Function<Bool, T, T>>(new Utils::DescendingKeyComparator<K, T>(key)));
        }
    }


    template<typename T>
    template<typename K>
    inline Tuple<T, Int> IterableCommon<T>::maxBy(Ptr<Function<K, T>> key) {
        return supremeWith(Ptr<Function<Bool, T, T>>(new Utils::AscendingKeyComparator<K, T>(key)));
    }


    template<typename T>
    template<typename K>
    inline Tuple<T, Int> IterableCommon<T>::minBy(Ptr<Function<K, T>> key) {
        return supremeWith(Ptr<Function<Bool, T, T>>(new Utils::DescendingKeyComparator<K, T>(key)));
    }


    template<typename T>
    template<Int dummy>
    inline Tuple<T, Int> IterableCommon<T>::max() {
        return supremeWith(Ptr<Function<Bool, T, T>>(new Utils::AscendingComparator<T>()));
    }


    template<typename T>
    template<Int dummy>
    inline Tuple<T, Int> IterableCommon<T>::min() {
        return supremeWith(Ptr<Function<Bool, T, T>>(new Utils::DescendingComparator<T>()));
    }


    template<typename T>
    template<typename R>
    inline Ptr<Iterable<R>> IterableCommon<T>::flatten() {
        return Ptr<Iterable<R>>(new Iterables::FlatteningIterable<T, R>(this->getSelf()));
    }


    template<typename T>
    template<typename R, typename Rs>
    inline Ptr<Iterable<R>> IterableCommon<T>::flatMap(Ptr<Function<Rs, T>> mapping) {
        auto mapped = map(mapping);  // T* -> Rs*
        return Ptr<Iterable<R>>(new Iterables::FlatteningIterable<Rs, R>(mapped));
    }


    template<typename T>
    inline Tuple<T, Int> IterableCommon<T>::supremeWith(Ptr<Function<Bool, T, T>> comparator) {
        auto iterator = getIterator();
        if (iterator->moveNext()) {
            auto bestItem = iterator->getCurrent();
            auto bestIndex = 0;

            auto index = 1;
            while (iterator->moveNext()) {
                auto item = iterator->getCurrent();
                if ((*comparator)(bestItem, item)) {
                    bestItem = item;
                    bestIndex = index;
                }
                index++;
            }

            return Tuple<T, Int>(bestItem, bestIndex);
        } else {
            throw EmptyIterableError();
        }
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


    template<typename T>
    inline Ptr<Iterable<Int>> IterableCommon<T>::getIndices() {
        return Ptr<Iterable<Int>>(new Iterables::IndexingIterable<T>(this->getSelf()));
    }


    template<typename T>
    inline Ptr<Iterable<T>> IterableCommon<T>::cons(T value) {
        auto node = makePtr<Iterables::ConstructingNode<T>>(value);
        return Ptr<Iterable<T>>(new Iterables::ConstructingIterable<T>(node, this->getSelf(), 1));
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
    inline Ptr<Iterable<T>> IterableCommon<T>::sortWith(Ptr<Function<Bool, T, T>> comparator) {
        auto vector = std::vector<T>();
        if (getHasLength()) {
            vector.reserve(getLength());
        }

        auto iterator = getIterator();
        while (iterator->moveNext()) {
            vector.push_back(iterator->getCurrent());
        }

        std::sort(vector.begin(), vector.end(), [comparator](T t1, T t2) {
            return (*comparator)(t1, t2);
        });

        return Ptr<Iterable<T>>(new Iterables::VectorIterable<T>(std::move(vector)));
    }


    template<typename T>
    inline Ptr<String> IterableCommon<T>::toString() {
        return Utils::join(L"::", this->getSelf(), L"", L"::[]");
    }
}
