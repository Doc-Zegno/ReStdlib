#pragma once

#include <vector>
#include <algorithm>
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
        ArrayList(Int number, T value);
        ArrayList(Ptr<Iterable<T>> items);
        ArrayList(std::initializer_list<T> list);

        virtual Ptr<Iterator<T>> getIterator() override;
        virtual Ptr<Iterable<T>> take(Int number) override;
        virtual Ptr<Iterable<T>> skip(Int number) override;
        virtual T getFirst() override;
        virtual T getLast() override;
        virtual Ptr<Iterable<T>> getRest() override;
        virtual T get(Int index) override;
        virtual Ptr<List<T>> getSlice(Int start, Int end, Int step) override;
        virtual Ptr<Iterable<Int>> getIndices() override;
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
        Int _length;

    public:
        ArrayListSlice(Ptr<ArrayList<T>> list, Int start, Int end, Int step);

        virtual Ptr<Iterator<T>> getIterator() override;
        virtual Ptr<Iterable<T>> take(Int number) override;
        virtual Ptr<Iterable<T>> skip(Int number) override;
        virtual T getFirst() override;
        virtual T getLast() override;
        virtual Ptr<Iterable<T>> getRest() override;
        virtual T get(Int index) override;
        virtual Ptr<List<T>> getSlice(Int start, Int end, Int step) override;
        virtual Ptr<Iterable<Int>> getIndices() override;
        virtual Int getLength() override;
        virtual Bool getHasLength() override;
        virtual Bool getIsEmpty() override;
        virtual Ptr<Iterable<T>> getSelf() override;

        T operator[](Int index);
    };
}


#include "Range.h"


namespace ReLang {
    // A r r a y L i s t
    template<typename T>
    inline ArrayList<T>::ArrayList(Int number, T value) : _vector(number, value) {
    }


    template<typename T>
    inline ArrayList<T>::ArrayList(Ptr<Iterable<T>> items) {
        if (items->getHasLength()) {
            // Reserve memory if possible
            _vector.reserve(items->getLength());
        }

        auto iterator = items->getIterator();
        while (iterator->moveNext()) {
            _vector.push_back(iterator->getCurrent());
        }
    }


    template<typename T>
    inline ArrayList<T>::ArrayList(std::initializer_list<T> list) : _vector(list) {
    }


    template<typename T>
    inline Ptr<Iterator<T>> ArrayList<T>::getIterator()
    {
        return Ptr<Iterator<T>>(
            new ArrayListIterator(
                this->shared_from_this()));
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayList<T>::take(Int number) {
        if (number >= 0) {
            auto length = Int(_vector.size());
            auto translatedNumber = std::min(number, length);  // Can't take more than actually exist
            return getSlice(0, translatedNumber, 1);
        } else {
            throw ValueError(L"Number of taken items should be non-negative");
        }
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayList<T>::skip(Int number) {
        if (number >= 0) {
            auto length = Int(_vector.size());
            auto translatedNumber = std::min(number, length);  // Can't skip more than actually exist
            return getSlice(translatedNumber, length, 1);
        } else {
            throw ValueError(L"Number of skipped items should be non-negative");
        }
    }


    template<typename T>
    inline T ArrayList<T>::getFirst() {
        if (!_vector.empty()) {
            return _vector[0];
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline T ArrayList<T>::getLast() {
        auto length = Int(_vector.size());
        if (length > 0) {
            return _vector[length - 1];
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayList<T>::getRest() {
        if (!_vector.empty()) {
            auto end = Int(_vector.size());
            return getSlice(1, end, 1);
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
        auto length = Int(_vector.size());
        auto translatedStart = start == length ? start : Utils::translateIndex(start, length);
        auto translatedEnd = end == length ? end : Utils::translateIndex(end, length);
        if (translatedEnd < translatedStart) {
            translatedEnd = translatedStart;
        }
        return Ptr<List<T>>(new ArrayListSlice<T>(this->shared_from_this(), translatedStart, translatedEnd, step));
    }


    template<typename T>
    inline Ptr<Iterable<Int>> ArrayList<T>::getIndices() {
        auto length = Int(_vector.size());
        return Ptr<Iterable<Int>>(new Range(0, length, 1));
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
        : _list(list), _start(start), _end(end), _step(step), _length((_end - _start + _step - 1) / _step)
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
    inline Ptr<Iterable<T>> ArrayListSlice<T>::take(Int number) {
        if (number >= 0) {
            auto translatedNumber = std::min(number, _length);  // Can't take more than actually exist
            return getSlice(0, translatedNumber, 1);
        } else {
            throw ValueError(L"Number of taken items should be non-negative");
        }
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayListSlice<T>::skip(Int number) {
        if (number >= 0) {
            auto translatedNumber = std::min(number, _length);  // Can't skip more than actually exist
            return getSlice(translatedNumber, _length, 1);
        } else {
            throw ValueError(L"Number of skipped items should be non-negative");
        }
    }


    template<typename T>
    inline T ArrayListSlice<T>::getFirst() {
        if (_start != _end) {
            return (*_list)[_start];
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline T ArrayListSlice<T>::getLast() {
        if (_length > 0) {
            auto lastIndex = _length - 1;
            return (*_list)[_start + lastIndex * _step];
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayListSlice<T>::getRest() {
        if (_length > 0) {
            return getSlice(1, _length, 1);
        } else {
            throw EmptyIterableError();
        }
    }


    template<typename T>
    inline T ArrayListSlice<T>::get(Int index) {
        return (*this)[index];
    }


    template<typename T>
    inline Ptr<List<T>> ArrayListSlice<T>::getSlice(Int start, Int end, Int step) {
        auto translatedStart = start == _length ? start : Utils::translateIndex(start, _length);
        auto translatedEnd = end == _length ? end : Utils::translateIndex(end, _length);
        if (translatedEnd < translatedStart) {
            translatedEnd = translatedStart;
        }
        return Ptr<List<T>>(new ArrayListSlice<T>(_list, _start + translatedStart * _step, _start + translatedEnd * _step, _step * step));
    }


    template<typename T>
    inline Ptr<Iterable<Int>> ArrayListSlice<T>::getIndices() {
        return Ptr<Iterable<Int>>(new Range(0, _length, 1));
    }


    template<typename T>
    inline Int ArrayListSlice<T>::getLength() {
        return _length;
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
        auto translatedIndex = Utils::translateIndex(index, _length);
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
