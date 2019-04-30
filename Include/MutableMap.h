#pragma once

#include "Map.h"
#include "MutableIterable.h"


namespace ReLang {
    template<typename Key, typename Value>
    class MutableMap : public Map<Key, Value>, public MutableIterable<Tuple<Key, Value>> {
    public:
        virtual void set(Key key, Value value) = 0;
        virtual void remove(Key key) = 0;
        virtual void clear() = 0;

        virtual Ptr<String> toString() override;
    };



    template<typename Key, typename Value>
    inline Ptr<String> MutableMap<Key, Value>::toString() {
        return Map<Key, Value>::toString();
    }
}