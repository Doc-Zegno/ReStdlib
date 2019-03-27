#pragma once

#include <vector>
#include <initializer_list>

#include "List.h"


namespace ReLang {
    template<typename T>
    class ArrayList : public List<T>, public EnableSelf<ArrayList<T>> {
    private:
        class ArrayListIterator : public Iterator<T>/*, EnableSelf<ArrayListIterator>*/ {
        private:
            Ptr<ArrayList> _list;
            std::vector<T>& _vector;
            Int _index;

        public:
            ArrayListIterator(Ptr<ArrayList> list, std::vector<T>& vector);

            virtual T getCurrent() override;
            virtual bool moveNext() override;

            //virtual Ptr<Any> getSelf() override;
        };


        std::vector<T> _vector;

    public:
        ArrayList(std::initializer_list<T> list);

        virtual Ptr<Iterator<T>> getIterator() override;
        virtual T __get__(Int index) override;
        virtual Ptr<Iterable<T>> getSelf() override;
    };



    template<typename T>
    inline ArrayList<T>::ArrayList(std::initializer_list<T> list)
        : _vector(list) { }


    template<typename T>
    inline Ptr<Iterator<T>> ArrayList<T>::getIterator()
    {
        return Ptr<Iterator<T>>(
            new ArrayListIterator(
                std::dynamic_pointer_cast<ArrayList<T>>(getSelf()),
                _vector));
    }


    template<typename T>
    inline T ArrayList<T>::__get__(Int index)
    {
        return _vector[index];
    }


    template<typename T>
    inline Ptr<Iterable<T>> ArrayList<T>::getSelf()
    {
        return this->shared_from_this();
    }



    template<typename T>
    inline ArrayList<T>::ArrayListIterator::ArrayListIterator(Ptr<ArrayList<T>> list, std::vector<T>& vector)
        : _list(list), _vector(vector), _index(-1) { }


    template<typename T>
    inline T ArrayList<T>::ArrayListIterator::getCurrent()
    {
        return _vector[_index];
    }


    template<typename T>
    inline bool ArrayList<T>::ArrayListIterator::moveNext()
    {
        _index++;
        auto maxLength = Int(_vector.size());
        if (_index >= maxLength) {
            _index = maxLength;
            return false;
        } else {
            return true;
        }
    }


    /*template<typename T>
    inline Ptr<Any> ArrayList<T>::ArrayListIterator::getSelf()
    {
        return this->shared_from_this();
    }*/
}

