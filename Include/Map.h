#pragma once

#include "Iterable.h"
#include "Equatable.h"
#include "Set.h"
#include "HashSet.h"


namespace ReLang {
    template<typename Key, typename Value>
    class Map : public virtual Iterable<Tuple<Key, Value>>, public virtual Equatable<Map<Key, Value>> {
    public:
        virtual Value get(Key key) = 0;
        virtual Ptr<Set<Key>> getKeys();
        virtual Ptr<Iterable<Value>> getValues();
		virtual Bool contains(Tuple<Key, Value> value) = 0;
        virtual Bool containsKey(Key key) = 0;
        virtual Ptr<Map<Key, Value>> getMapSelf() = 0;

        virtual Bool operator==(Ptr<Map<Key, Value>> other) override;
        virtual Ptr<String> toString(Bool isEscaped = false) override;
    };



    namespace Iterables {
        template<typename Key, typename Value>
        class MapKeys : public Set<Key>, public EnableSelf<MapKeys<Key, Value>> {
        private:
            class MapKeysIterator : public Iterator<Key> {
            private:
                Ptr<Iterator<Tuple<Key, Value>>> _iterator;

            public:
                MapKeysIterator(Ptr<Iterator<Tuple<Key, Value>>> iterator);

                virtual Key getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<Key>> clone() override;
            };


            Ptr<Map<Key, Value>> _map;

        public:
            MapKeys(Ptr<Map<Key, Value>> map);

            virtual Ptr<Set<Key>> unioned(Ptr<Iterable<Key>> items) override;
            virtual Ptr<Set<Key>> intersection(Ptr<Iterable<Key>> items) override;
            virtual Ptr<Set<Key>> difference(Ptr<Iterable<Key>> items) override;

            virtual Ptr<Iterable<Key>> getSelf() override;
            virtual Ptr<Iterator<Key>> getIterator() override;
            virtual Bool contains(Key key) override;
            virtual Bool getIsEmpty() override;
            virtual Bool getHasLength() override;
            virtual Int getLength() override;
        };



        template<typename Key, typename Value>
        class MapValues : public Iterable<Value>, public EnableSelf<MapValues<Key, Value>> {
        private:
            class MapValuesIterator : public Iterator<Value> {
            private:
                Ptr<Iterator<Tuple<Key, Value>>> _iterator;

            public:
                MapValuesIterator(Ptr<Iterator<Tuple<Key, Value>>> iterator);

                virtual Value getCurrent() override;
                virtual Bool moveNext() override;
                virtual Ptr<Iterator<Value>> clone() override;
            };


            Ptr<Map<Key, Value>> _map;

        public:
            MapValues(Ptr<Map<Key, Value>> map);

            virtual Ptr<Iterable<Value>> getSelf() override;
            virtual Ptr<Iterator<Value>> getIterator() override;
            virtual Bool getIsEmpty() override;
            virtual Bool getHasLength() override;
            virtual Int getLength() override;
        };



        // M a p K e y s
        template<typename Key, typename Value>
        inline MapKeys<Key, Value>::MapKeys(Ptr<Map<Key, Value>> map) : _map(map) {
        }


        template<typename Key, typename Value>
        inline Ptr<Set<Key>> MapKeys<Key, Value>::unioned(Ptr<Iterable<Key>> items) {
            auto set = makeSet<Key>(this->getSelf());
            set->addAll(items);
            return set;
        }


        template<typename Key, typename Value>
        inline Ptr<Set<Key>> MapKeys<Key, Value>::intersection(Ptr<Iterable<Key>> items) {
            auto set = makeSet<Key>(this->getSelf());
            return set->intersection(items);
        }


        template<typename Key, typename Value>
        inline Ptr<Set<Key>> MapKeys<Key, Value>::difference(Ptr<Iterable<Key>> items) {
            auto set = makeSet<Key>(this->getSelf());
            set->removeAll(items);
            return set;
        }


        template<typename Key, typename Value>
        inline Ptr<Iterable<Key>> MapKeys<Key, Value>::getSelf() {
            return this->shared_from_this();
        }


        template<typename Key, typename Value>
        inline Ptr<Iterator<Key>> MapKeys<Key, Value>::getIterator() {
            return makePtr<MapKeysIterator>(_map->getIterator());
        }


        template<typename Key, typename Value>
        inline Bool MapKeys<Key, Value>::contains(Key key) {
            return _map->containsKey(key);
        }


        template<typename Key, typename Value>
        inline Bool MapKeys<Key, Value>::getIsEmpty() {
            return _map->getIsEmpty();
        }


        template<typename Key, typename Value>
        inline Bool MapKeys<Key, Value>::getHasLength() {
            return _map->getHasLength();
        }


        template<typename Key, typename Value>
        inline Int MapKeys<Key, Value>::getLength() {
            return _map->getLength();
        }



        // M a p K e y s I t e r a t o r
        template<typename Key, typename Value>
        inline MapKeys<Key, Value>::MapKeysIterator::MapKeysIterator(Ptr<Iterator<Tuple<Key, Value>>> iterator)
            : _iterator(iterator)
        {
        }


        template<typename Key, typename Value>
        inline Key MapKeys<Key, Value>::MapKeysIterator::getCurrent() {
            auto tuple = _iterator->getCurrent();
            return tuple.getFirst();
        }


        template<typename Key, typename Value>
        inline Bool MapKeys<Key, Value>::MapKeysIterator::moveNext() {
            return _iterator->moveNext();
        }


        template<typename Key, typename Value>
        inline Ptr<Iterator<Key>> MapKeys<Key, Value>::MapKeysIterator::clone() {
            return makePtr<MapKeysIterator>(_iterator->clone());
        }



        // M a p V a l u e s
        template<typename Key, typename Value>
        inline MapValues<Key, Value>::MapValues(Ptr<Map<Key, Value>> map) : _map(map) {
        }


        template<typename Key, typename Value>
        inline Ptr<Iterable<Value>> MapValues<Key, Value>::getSelf() {
            return this->shared_from_this();
        }


        template<typename Key, typename Value>
        inline Ptr<Iterator<Value>> MapValues<Key, Value>::getIterator() {
            return makePtr<MapValuesIterator>(_map->getIterator());
        }


        template<typename Key, typename Value>
        inline Bool MapValues<Key, Value>::getIsEmpty() {
            return _map->getIsEmpty();
        }


        template<typename Key, typename Value>
        inline Bool MapValues<Key, Value>::getHasLength() {
            return _map->getHasLength();
        }


        template<typename Key, typename Value>
        inline Int MapValues<Key, Value>::getLength() {
            return _map->getLength();
        }



        // M a p V a l u e s I t e r a t o r
        template<typename Key, typename Value>
        inline MapValues<Key, Value>::MapValuesIterator::MapValuesIterator(Ptr<Iterator<Tuple<Key, Value>>> iterator)
            : _iterator(iterator)
        {
        }


        template<typename Key, typename Value>
        inline Value MapValues<Key, Value>::MapValuesIterator::getCurrent() {
            return _iterator->getCurrent().getSecond();
        }


        template<typename Key, typename Value>
        inline Bool MapValues<Key, Value>::MapValuesIterator::moveNext() {
            return _iterator->moveNext();
        }


        template<typename Key, typename Value>
        inline Ptr<Iterator<Value>> MapValues<Key, Value>::MapValuesIterator::clone() {
            return makePtr<MapValuesIterator>(_iterator->clone());
        }
    }



    // M a p
    template<typename Key, typename Value>
    inline Ptr<Set<Key>> Map<Key, Value>::getKeys() {
        return makePtr<Iterables::MapKeys<Key, Value>>(this->getMapSelf());
    }


    template<typename Key, typename Value>
    inline Ptr<Iterable<Value>> Map<Key, Value>::getValues() {
        return makePtr<Iterables::MapValues<Key, Value>>(this->getMapSelf());
    }


    template<typename Key, typename Value>
    inline Bool Map<Key, Value>::operator==(Ptr<Map<Key, Value>> other) {
        if (this->getHasLength() && other->getHasLength()) {
            if (this->getLength() != other->getLength()) {
                return false;
            }
        }

        auto iterator = other->getIterator();
        while (iterator->moveNext()) {
            if (!this->contains(iterator->getCurrent())) {
                return false;
            }
        }

        return true;
    }


    template<typename Key, typename Value>
    inline Ptr<String> Map<Key, Value>::toString(Bool isEscaped) {
        return Utils::joinPairs(L", ", this->getSelf(), L"{", L"}");
    }
}
