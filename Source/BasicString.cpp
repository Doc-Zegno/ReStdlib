#include "BasicString.h"

#include <sstream>

#include "Errors.h"


namespace ReLang {
    class StringIterator : public Iterator<Char> {
    private:
        Ptr<String> _string;
        Int _index;
        Int _end;

    public:
        StringIterator(Ptr<String> string) : _string(string), _index(-1), _end(Int(string->getLength())) {}

        virtual Char getCurrent() override {
            return (*_string)[_index];
        }

        virtual bool moveNext() override {
            _index++;
            if (_index >= _end) {
                _index = _end;
                return false;
            } else {
                return true;
            }
        }
    };


    String::String(const Char* string) : _raw(string) {
    }


    String::String(const std::wstring& string) : _raw(string) {
    }


    String::String(std::wstring&& string) : _raw(std::move(string)) {
    }


    String::String(Int count, Char character) : _raw(count, character) {
    }


    Ptr<Iterable<Char>> String::getSelf() {
        return this->shared_from_this();
    }


    Ptr<Iterator<Char>> String::getIterator() {
        return Ptr<Iterator<Char>>(new StringIterator(this->shared_from_this()));
    }


    Char String::getFirst() {
        return operator[](0);
    }


    Char String::getLast() {
        auto lastIndex = Int(_raw.size()) - 1;
        return operator[](lastIndex);
    }


    Ptr<Iterable<Char>> String::getRest() {
        // TODO: String slice
        return Ptr<Iterable<Char>>();
    }


    Bool String::getIsEmpty() {
        return _raw.empty();
    }


    Int String::getLength() {
        return Int(_raw.size());
    }


    Bool String::getHasLength() {
        return true;
    }


    Char String::__get__(Int index) {
        return this->operator[](index);
    }


    Ptr<String> String::toString() {
        return this->shared_from_this();
    }


    Char String::operator[](Int index) {
        auto end = Int(_raw.size());
        if (index >= 0 && index < end) {
            return _raw[index];
        } else {
            throw IndexError(index, end);
        }
    }


    const std::wstring& String::getRaw() const {
        return _raw;
    }


    std::wostream & operator<<(std::wostream& out, Ptr<String> string) {
        out << string->getRaw();
        return out;
    }
}