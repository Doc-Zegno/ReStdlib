#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

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
            ArrayListIterator(Ptr<ArrayList> list);

            virtual T getCurrent() override;
            virtual bool moveNext() override;
        };


        std::vector<T> _vector;

    public:
        ArrayList(std::initializer_list<T> list);

        virtual Ptr<Iterator<T>> getIterator() override;
        virtual T __get__(Int index) override;
        virtual Int getLength() override;
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
    inline T ArrayList<T>::__get__(Int index)
    {
        return (*this)[index];
    }


    template<typename T>
    inline Int ArrayList<T>::getLength() {
        return Int(_vector.size());
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
    inline ArrayList<T>::ArrayListIterator::ArrayListIterator(Ptr<ArrayList<T>> list)
        : _list(list), _index(-1), _maximumIndex(list->getLength()) { }


    template<typename T>
    inline T ArrayList<T>::ArrayListIterator::getCurrent()
    {
        return (*_list)[_index];
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
}


#endif
