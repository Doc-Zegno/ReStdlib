#pragma once

#include <unordered_map>

#include "MutableMap.h"
#include "Utils/HashUtils.h"
#include "Utils/OperatorUtils.h"


namespace ReLang {
    template<typename Key, typename Value>
    class HashMap : public MutableMap<Key, Value>, public EnableSelf<HashMap<Key, Value>> {
    public:
        using InternalMap = std::unordered_map<Key, Value, Utils::Hash<Key>, Utils::EqualityComparator<Value>>;
        using InternalMapIterator = typename InternalMap::iterator;

    private:
        class HashMapIterator : public MutatingIterator<Tuple<Key, Value>> {
        private:
            InternalMapIterator _current;
            InternalMapIterator _end;
            Bool _isStarted;
            Bool _isValid;

        public:
            HashMapIterator(InternalMapIterator current, InternalMapIterator end, Bool isStarted, Bool isValid);

            virtual Tuple<Key, Value> getCurrent() override;
            virtual void setCurrent(Tuple<Key, Value> pair) override;
            virtual Bool moveNext() override;
            virtual Ptr<Iterator<Tuple<Key, Value>>> clone() override;
        };


        InternalMap _map;
    
    public:
        HashMap();
        HashMap(InternalMap&& map);
        HashMap(Ptr<Iterable<Tuple<Key, Value>>> items);
        HashMap(std::initializer_list<Tuple<Key, Value>> list);

        virtual Ptr<Iterable<Tuple<Key, Value>>> getSelf() override;
        virtual Ptr<Iterator<Tuple<Key, Value>>> getIterator() override;
        virtual Ptr<MutatingIterator<Tuple<Key, Value>>> getMutatingIterator() override;
        virtual Bool contains(Tuple<Key, Value> value) override;
        virtual Bool getIsEmpty() override;
        virtual Bool getHasLength() override;
        virtual Int getLength() override;

        virtual Value get(Key key) override;
        virtual Ptr<Set<Key>> getKeys() override;
        virtual Ptr<Iterable<Value>> getValues() override;
        virtual Bool containsKey(Key key) override;
        virtual void set(Key key, Value value) override;
        virtual void remove(Key key) override;
        virtual void clear() override;
        virtual Ptr<Map<Key, Value>> getMapSelf() override;
    };



    // H a s h M a p
    template<typename Key, typename Value>
    inline HashMap<Key, Value>::HashMap() {
    }


    template<typename Key, typename Value>
    inline HashMap<Key, Value>::HashMap(InternalMap&& map) : _map(std::move(map)) {
    }


    template<typename Key, typename Value>
    inline HashMap<Key, Value>::HashMap(Ptr<Iterable<Tuple<Key, Value>>> items) {
        if (items->getHasLength()) {
            _map.reserve(items->getLength());
        }

        auto iterator = items->getIterator();
        while (iterator->moveNext()) {
            auto pair = iterator->getCurrent();
            auto first = pair.getFirst();
            auto second = pair.getSecond();
            _map[first] = second;
        }
    }


    template<typename Key, typename Value>
    inline HashMap<Key, Value>::HashMap(std::initializer_list<Tuple<Key, Value>> list) {
        _map.reserve(list.size());

        for (auto pair : list) {
            auto first = pair.getFirst();
            auto second = pair.getSecond();
            _map[first] = second;
        }
    }


    template<typename Key, typename Value>
    inline Ptr<Iterable<Tuple<Key, Value>>> HashMap<Key, Value>::getSelf() {
        return this->shared_from_this();
    }


    template<typename Key, typename Value>
    inline Ptr<Iterator<Tuple<Key, Value>>> HashMap<Key, Value>::getIterator() {
        return makePtr<HashMapIterator>(_map.begin(), _map.end(), false, false);
    }


    template<typename Key, typename Value>
    inline Ptr<MutatingIterator<Tuple<Key, Value>>> HashMap<Key, Value>::getMutatingIterator() {
        return makePtr<HashMapIterator>(_map.begin(), _map.end(), false, false);
    }


    template<typename Key, typename Value>
    inline Bool HashMap<Key, Value>::contains(Tuple<Key, Value> value) {
        auto key = value.getFirst();
        auto it = _map.find(key);
        if (it != _map.end()) {
            auto pair = *it;
            return Utils::equals(pair.second, value.getSecond());
        } else {
            return false;
        }
    }


    template<typename Key, typename Value>
    inline Bool HashMap<Key, Value>::getIsEmpty() {
        return _map.empty();
    }


    template<typename Key, typename Value>
    inline Bool HashMap<Key, Value>::getHasLength() {
        return true;
    }


    template<typename Key, typename Value>
    inline Int HashMap<Key, Value>::getLength() {
        return Int(_map.size());
    }


    template<typename Key, typename Value>
    inline Value HashMap<Key, Value>::get(Key key) {
        auto it = _map.find(key);
        if (it != _map.end()) {
            return it->second;
        } else {
            throw KeyError();
        }
    }


    template<typename Key, typename Value>
    inline Ptr<Set<Key>> HashMap<Key, Value>::getKeys() {
        // TODO: implement
        throw NotImplementedError();
    }


    template<typename Key, typename Value>
    inline Ptr<Iterable<Value>> HashMap<Key, Value>::getValues() {
        // TODO: implement
        throw NotImplementedError();
    }


    template<typename Key, typename Value>
    inline Bool HashMap<Key, Value>::containsKey(Key key) {
        return _map.find(key) != _map.end();
    }


    template<typename Key, typename Value>
    inline void HashMap<Key, Value>::set(Key key, Value value) {
        _map[key] = value;
    }


    template<typename Key, typename Value>
    inline void HashMap<Key, Value>::remove(Key key) {
        _map.erase(key);
    }


    template<typename Key, typename Value>
    inline void HashMap<Key, Value>::clear() {
        _map.clear();
    }


    template<typename Key, typename Value>
    inline Ptr<Map<Key, Value>> HashMap<Key, Value>::getMapSelf() {
        return this->shared_from_this();
    }



    // H a s h M a p I t e r a t o r
    template<typename Key, typename Value>
    inline HashMap<Key, Value>::HashMapIterator::HashMapIterator(InternalMapIterator current, InternalMapIterator end, Bool isStarted, Bool isValid)
        : _current(current), _end(end), _isStarted(isStarted), _isValid(isValid)
    {
    }


    template<typename Key, typename Value>
    inline Tuple<Key, Value> HashMap<Key, Value>::HashMapIterator::getCurrent() {
        if (_isValid) {
            return Tuple<Key, Value>(_current->first, _current->second);
        } else {
            throw InvalidIteratorError();
        }
    }


    template<typename Key, typename Value>
    inline void HashMap<Key, Value>::HashMapIterator::setCurrent(Tuple<Key, Value> pair) {
        throw NotSupportedError(L"Iterator for HashMap doesn't support method .setCurrent()");
    }


    template<typename Key, typename Value>
    inline Bool HashMap<Key, Value>::HashMapIterator::moveNext() {
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


    template<typename Key, typename Value>
    inline Ptr<Iterator<Tuple<Key, Value>>> HashMap<Key, Value>::HashMapIterator::clone() {
        return makePtr<HashMapIterator>(_current, _end, _isStarted, _isValid);
    }
}
