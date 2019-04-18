#pragma once

#include <vector>
#include <initializer_list>

#include "List.h"
#include "Errors.h"
#include "Utils/IterableUtils.h"


namespace ReLang {
    template<typename T>
    class ArrayList : public List<T>, public EnableSelf<ArrayList<T>> {
    private:
        class ArrayListIterator : public Iterator<T> {
        private:
            Ptr<ArrayList> _list;
            Int _index;
            Int _maximumIndex;

        public:
            ArrayListIterator(Ptr<ArrayList> list, Int index = -1);

            virtual T getCurrent() override;
            virtual Bool moveNext() override;
            virtual Ptr<Iterator<T>> clone() override;
        };


        std::vector<T> _vector;

    public:
        ArrayList(std::initializer_list<T> list);

        virtual Ptr<Iterator<T>> getIterator() override;
        virtual Ptr<Iterable<T>> take(Int number) override;
        virtual Ptr<Iterable<T>> skip(Int number) override;
        virtual Ptr<Iterable<T>> getRest() override;
        virtual T get(Int index) override;
        virtual Ptr<List<T>> getSlice(Int start, Int end, Int step) override;
        virtual Int getLength() override;
        virtual Bool getHasLength() override;
        virtual Bool getIsEmpty() override;
        virtual Ptr<Iterable<T>> getSelf() override;

        T operator[](Int index);
    };



    template<typename T>
    class ArrayListSlice : public List<T>, public EnableSelf<ArrayListSlice<T>> {
    private:
        class ArrayListSliceIterator : public Iterator<T> {
        private:
            Ptr<ArrayListSlice> _slice;
            Int _index;
            Int _maximumIndex;

        public:
            ArrayListSliceIterator(Ptr<ArrayListSlice> slice, Int index = -1);

            virtual T getCurrent() override;
            virtual Bool moveNext() override;
            virtual Ptr<Iterator<T>> clone() override;
        };


        Ptr<ArrayList<T>> _list;
        Int _start;
        Int _end;
        Int _step;

    public:
        ArrayListSlice(Ptr<ArrayList<T>> list, Int start, Int end, Int step);

        virtual Ptr<Iterator<T>> getIterator() override;
        virtual T get(Int index) override;
        virtual Ptr<List<T>> getSlice(Int start, Int end, Int step) override;
        virtual Int getLength() override;
        virtual Bool getHasLength() override;
        virtual Bool getIsEmpty() override;
        virtual Ptr<Iterable<T>> getSelf() override;

        T operator[](Int index);
    };



    // A r r a y L i s t
    template<typename T>
    inline ArrayList<T>::ArrayList(std::initializer_list<T> list)
        : _vector(list) { }


    template<typename T>
    inline Ptr<Iterator<T>> ArrayList<T>::getIterator()
    {
        return Ptr<Iterator<T>>(
            new ArrayListIterator(
                this->shared_from_this()));
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayList<T>::take(Int number) {
        return Ptr<List<T>>(new ArrayListSlice<T>(this->shared_from_this(), 0, number, 1));
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayList<T>::skip(Int number) {
        auto end = Int(_vector.size());
        return Ptr<List<T>>(new ArrayListSlice<T>(this->shared_from_this(), number, end, 1));
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayList<T>::getRest() {
        if (!_vector.empty()) {
            auto end = Int(_vector.size());
            return Ptr<List<T>>(new ArrayListSlice<T>(this->shared_from_this(), 1, end, 1));
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline T ArrayList<T>::get(Int index)
    {
        return (*this)[index];
    }


    template<typename T>
    inline Ptr<List<T>> ArrayList<T>::getSlice(Int start, Int end, Int step) {
        return Ptr<List<T>>(new ArrayListSlice<T>(this->shared_from_this(), start, end, step));
    }


    template<typename T>
    inline Int ArrayList<T>::getLength() {
        return Int(_vector.size());
    }


    template<typename T>
    inline Bool ArrayList<T>::getHasLength() {
        return true;
    }


    template<typename T>
    inline Bool ArrayList<T>::getIsEmpty() {
        return _vector.empty();
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayList<T>::getSelf()
    {
        return this->shared_from_this();
    }


    template<typename T>
    inline T ArrayList<T>::operator[](Int index) {
        auto end = Int(_vector.size());
        auto translatedIndex = Utils::translateIndex(index, end);
        return _vector[translatedIndex];
    }



    // A r r a y L i s t I t e r a t o r
    template<typename T>
    inline ArrayList<T>::ArrayListIterator::ArrayListIterator(Ptr<ArrayList<T>> list, Int index)
        : _list(list), _index(index), _maximumIndex(list->getLength()) { }


    template<typename T>
    inline T ArrayList<T>::ArrayListIterator::getCurrent()
    {
        if (_index >= 0 && _index < _maximumIndex) {
            return (*_list)[_index];
        } else {
            throw InvalidIteratorError();
        }
    }


    template<typename T>
    inline Bool ArrayList<T>::ArrayListIterator::moveNext()
    {
        _index++;
        if (_index >= _maximumIndex) {
            _index = _maximumIndex;
            return false;
        } else {
            return true;
        }
    }


    template<typename T>
    inline Ptr<Iterator<T>> ArrayList<T>::ArrayListIterator::clone() {
        return Ptr<Iterator<T>>(new ArrayListIterator(_list, _index));
    }



    // A r r a y L i s t S l i c e
    template<typename T>
    inline ArrayListSlice<T>::ArrayListSlice(Ptr<ArrayList<T>> list, Int start, Int end, Int step)
        : _list(list), _start(start), _end(end), _step(step)
    {
        // TODO: check actual length of underlying list
        // and adjust start/end if necessary
        if (step <= 0) {
            throw ValueError(L"Slice must have a positive step");
        }
    }


    template<typename T>
    inline Ptr<Iterator<T>> ArrayListSlice<T>::getIterator() {
        return Ptr<Iterator<T>>(new ArrayListSliceIterator(this->shared_from_this()));
    }


    template<typename T>
    inline T ArrayListSlice<T>::get(Int index) {
        return (*this)[index];
    }


    template<typename T>
    inline Ptr<List<T>> ArrayListSlice<T>::getSlice(Int start, Int end, Int step) {
        return Ptr<List<T>>(new ArrayListSlice<T>(_list, _start + start * _step, _start + end * _step, _step * step));
    }


    template<typename T>
    inline Int ArrayListSlice<T>::getLength() {
        return (_end - _start + _step - 1) / _step;
    }


    template<typename T>
    inline Bool ArrayListSlice<T>::getHasLength() {
        return true;
    }


    template<typename T>
    inline Bool ArrayListSlice<T>::getIsEmpty() {
        return _end == _start;
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayListSlice<T>::getSelf() {
        return this->shared_from_this();
    }


    template<typename T>
    inline T ArrayListSlice<T>::operator[](Int index) {
        auto length = (_end - _start + _step - 1) / _step;
        auto translatedIndex = Utils::translateIndex(index, length);
        return (*_list)[_start + translatedIndex * _step];
    }



    // A r r a y L i s t S l i c e I t e r a t o r
    template<typename T>
    inline ArrayListSlice<T>::ArrayListSliceIterator::ArrayListSliceIterator(Ptr<ArrayListSlice> slice, Int index)
        : _slice(slice), _index(index), _maximumIndex(slice->getLength())
    {
    }


    template<typename T>
    inline T ArrayListSlice<T>::ArrayListSliceIterator::getCurrent() {
        if (_index >= 0 && _index < _maximumIndex) {
            return (*_slice)[_index];
        } else {
            throw InvalidIteratorError();
        }
    }


    template<typename T>
    inline Bool ArrayListSlice<T>::ArrayListSliceIterator::moveNext() {
        _index++;
        if (_index < _maximumIndex) {
            return true;
        } else {
            _index = _maximumIndex;
            return false;
        }
    }


    template<typename T>
    inline Ptr<Iterator<T>> ArrayListSlice<T>::ArrayListSliceIterator::clone() {
        return Ptr<Iterator<T>>(new ArrayListSliceIterator(_slice, _index));
    }
}
