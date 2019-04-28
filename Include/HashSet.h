#pragma once

#include <unordered_set>
#include <initializer_list>

#include "MutableSet.h"
#include "Utils/OperatorUtils.h"
#include "Utils/HashUtils.h"


namespace ReLang {
    template<typename T>
    class HashSet : public MutableSet<T>, public EnableSelf<HashSet<T>> {
    public:
        using InternalSet = std::unordered_set<T, Utils::Hash<T>, Utils::EqualityComparator<T>>;
        using InternalSetIterator = typename InternalSet::iterator;

    private:
        class HashSetIterator : public MutatingIterator<T> {
        private:
            InternalSetIterator _current;
            InternalSetIterator _end;
            Bool _isStarted;
            Bool _isValid;

        public:
            HashSetIterator(InternalSetIterator current, InternalSetIterator end, Bool isStarted, Bool isValid);

            virtual T getCurrent() override;
            virtual void setCurrent(T value) override;
            virtual Bool moveNext() override;
            virtual Ptr<Iterator<T>> clone() override;
        };


        InternalSet _set;

    public:
        HashSet();
        HashSet(InternalSet&& set);
        HashSet(std::initializer_list<T> list);
        HashSet(Ptr<Iterable<T>> items);

        virtual Ptr<Iterable<T>> getSelf() override;
        virtual Ptr<Iterator<T>> getIterator() override;
        virtual Ptr<MutatingIterator<T>> getMutatingIterator() override;

        virtual Ptr<Set<T>> unioned(Ptr<Iterable<T>> items) override;
        virtual Ptr<Set<T>> intersection(Ptr<Iterable<T>> items) override;
        virtual Ptr<Set<T>> difference(Ptr<Iterable<T>> items) override;

        virtual void add(T value) override;
        virtual void addAll(Ptr<Iterable<T>> values) override;
        virtual void remove(T value) override;
        virtual void removeAll(Ptr<Iterable<T>> values) override;
    };



    // H a s h S e t
    template<typename T>
    inline HashSet<T>::HashSet() {
    }


    template<typename T>
    inline HashSet<T>::HashSet(InternalSet&& set) : _set(std::move(set)) {
    }


    template<typename T>
    inline HashSet<T>::HashSet(std::initializer_list<T> list) {
        _set.reserve(list.size());
        for (auto item : list) {
            _set.insert(item);
        }
    }


    template<typename T>
    inline HashSet<T>::HashSet(Ptr<Iterable<T>> items) {
        if (items->getHasLength()) {
            _set.reserve(items->getLength());
        }

        auto iterator = items->getIterator();
        while (iterator->moveNext()) {
            _set.insert(iterator->getCurrent());
        }
    }


    template<typename T>
    inline Ptr<Iterable<T>> HashSet<T>::getSelf() {
        return this->shared_from_this();
    }


    template<typename T>
    inline Ptr<Iterator<T>> HashSet<T>::getIterator() {
        return makePtr<HashSetIterator>(_set.begin(), _set.end(), false, false);
    }


    template<typename T>
    inline Ptr<MutatingIterator<T>> HashSet<T>::getMutatingIterator() {
        return makePtr<HashSetIterator>(_set.begin(), _set.end(), false, false);
    }


    template<typename T>
    inline Ptr<Set<T>> HashSet<T>::unioned(Ptr<Iterable<T>> items) {
        auto set = _set;

        auto iterator = items->getIterator();
        while (iterator->moveNext()) {
            set.insert(iterator->getCurrent());
        }

        return makePtr<HashSet<T>>(std::move(set));
    }


    template<typename T>
    inline Ptr<Set<T>> HashSet<T>::intersection(Ptr<Iterable<T>> items) {
        auto set = InternalSet();

        auto end = _set.end();
        auto iterator = items->getIterator();
        while (iterator->moveNext()) {
            auto item = iterator->getCurrent();
            if (_set.find(item) != end) {
                // Common element
                set.insert(item);
            }
        }

        return makePtr<HashSet<T>>(std::move(set));
    }


    template<typename T>
    inline Ptr<Set<T>> HashSet<T>::difference(Ptr<Iterable<T>> items) {
        auto set = _set;

        auto iterator = items->getIterator();
        while (iterator->moveNext()) {
            set.erase(iterator->getCurrent());
        }

        return makePtr<HashSet<T>>(std::move(set));
    }


    template<typename T>
    inline void HashSet<T>::add(T value) {
        _set.insert(value);
    }


    template<typename T>
    inline void HashSet<T>::addAll(Ptr<Iterable<T>> values) {
        auto iterator = values->getIterator();
        while (iterator->moveNext()) {
            _set.insert(iterator->getCurrent());
        }
    }


    template<typename T>
    inline void HashSet<T>::remove(T value) {
        _set.erase(value);
    }


    template<typename T>
    inline void HashSet<T>::removeAll(Ptr<Iterable<T>> values) {
        auto iterator = values->getIterator();
        while (iterator->moveNext()) {
            _set.erase(iterator->getCurrent());
        }
    }



    // H a s h S e t I t e r a t o r
    template<typename T>
    inline HashSet<T>::HashSetIterator::HashSetIterator(InternalSetIterator current, InternalSetIterator end, Bool isStarted, Bool isValid)
        : _current(current), _end(end), _isStarted(isStarted), _isValid(isValid)
    {
    }


    template<typename T>
    inline T HashSet<T>::HashSetIterator::getCurrent() {
        if (_isValid) {
            return *_current;
        } else {
            throw InvalidIteratorError();
        }
    }


    template<typename T>
    inline void HashSet<T>::HashSetIterator::setCurrent(T value) {
        throw NotSupportedError(L"Iterator for HashSet doesn't support method .setCurrent()");
    }


    template<typename T>
    inline Bool HashSet<T>::HashSetIterator::moveNext() {
        if (_current != _end) {
            if (!_isStarted) {
                _isStarted = true;
                _isValid = true;
                return true;
            } else {
                _current++;
                if (_current != _end) {
                    return true;
                }
            } 
        }
        _isValid = false;
        return false;
    }


    template<typename T>
    inline Ptr<Iterator<T>> HashSet<T>::HashSetIterator::clone() {
        return Ptr<Iterator<T>>(new HashSetIterator(_current, _end, _isStarted, _isValid));
    }
}
