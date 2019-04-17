#pragma once

#include <vector>
#include <initializer_list>

#include "List.h"
#include "Errors.h"


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
            ArrayListIterator(Ptr<ArrayList> list, int index = -1);

            virtual T getCurrent() override;
            virtual bool moveNext() override;
            virtual Ptr<Iterator<T>> clone() override;
        };


        std::vector<T> _vector;

    public:
        ArrayList(std::initializer_list<T> list);

        virtual Ptr<Iterator<T>> getIterator() override;
        virtual T get(Int index) override;
        virtual Int getLength() override;
        virtual Bool getHasLength() override;
        virtual Bool getIsEmpty() override;
        virtual Ptr<Iterable<T>> getSelf() override;

        T operator[](Int index);
    };



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
    inline T ArrayList<T>::get(Int index)
    {
        return (*this)[index];
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
        if (index >= 0 && index < end) {
            return _vector[index];
        } else {
            throw IndexError(index, end);
        }
    }



    template<typename T>
    inline ArrayList<T>::ArrayListIterator::ArrayListIterator(Ptr<ArrayList<T>> list, int index)
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
    inline bool ArrayList<T>::ArrayListIterator::moveNext()
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
}
