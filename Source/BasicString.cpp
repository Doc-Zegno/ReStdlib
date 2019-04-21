#include "BasicString.h"

#include <sstream>
#include <algorithm>

#include "Errors.h"
#include "Range.h"
#include "Utils/IterableUtils.h"


namespace ReLang {
    class StringIterator : public Iterator<Char> {
    private:
        Ptr<String> _string;
        Int _index;
        Int _end;

    public:
        StringIterator(Ptr<String> string, int index = -1) : _string(string), _index(index), _end(Int(string->getLength())) {}

        virtual Char getCurrent() override {
            if (_index >= 0 && _index < _end) {
                return (*_string)[_index];
            } else {
                throw InvalidIteratorError();
            }
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

        virtual Ptr<Iterator<Char>> clone() override {
            return Ptr<Iterator<Char>>(new StringIterator(_string, _index));
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


    Ptr<Iterable<Char>> String::take(Int number) {
        if (number >= 0) {
            auto length = Int(_raw.size());
            auto translatedNumber = std::min(number, length);  // Can't take more than actually exist
            return getSlice(0, translatedNumber, 1);
        } else {
            throw ValueError(L"Number of taken items should be non-negative");
        }
    }


    Ptr<Iterable<Char>> String::skip(Int number) {
        if (number >= 0) {
            auto length = Int(_raw.size());
            auto translatedNumber = std::min(number, length);  // Can't skip more than actually exist
            return getSlice(translatedNumber, length, 1);
        } else {
            throw ValueError(L"Number of skipped items should be non-negative");
        }
    }


    Char String::getFirst() {
        if (!_raw.empty()) {
            return _raw[0];
        } else {
            throw EmptyIterableError();
        }
    }


    Char String::getLast() {
        auto length = Int(_raw.size());
        if (length > 0) {
            return _raw[length - 1];
        } else {
            throw EmptyIterableError();
        }
    }


    Ptr<Iterable<Char>> String::getRest() {
        auto length = Int(_raw.size());
        if (length > 0) {
            return getSlice(1, length, 1);
        } else {
            throw EmptyIterableError();
        }
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


    Char String::get(Int index) {
        return (*this)[index];
    }


    Ptr<List<Char>> String::getSlice(Int start, Int end, Int step) {
        if (step > 0) {
            auto length = Int(_raw.size());
            auto translatedStart = start == length ? start : Utils::translateIndex(start, length);
            auto translatedEnd = end == length ? end : Utils::translateIndex(end, length);
            if (translatedEnd < translatedStart) {
                translatedEnd = translatedStart;
            }

            auto capacity = (translatedEnd - translatedStart + step - 1) / step;
            auto buffer = std::wstring(capacity, L'\0');
            auto j = 0;
            for (auto i = translatedStart; i < translatedEnd; i += step) {
                buffer[j] = _raw[i];
                j++;
            }
            buffer.resize(j);
            return makePtr<String>(std::move(buffer));
        } else {
            throw ValueError(L"Step of slice must be positive");
        }
    }


    inline Ptr<Iterable<Int>> String::getIndices() {
        auto length = Int(_raw.size());
        return Ptr<Iterable<Int>>(new Range(0, length, 1));
    }


    Ptr<String> String::toString() {
        return this->shared_from_this();
    }


    Char String::operator[](Int index) {
        auto end = Int(_raw.size());
        auto translatedIndex = Utils::translateIndex(index, end);
        return _raw[translatedIndex];
    }


    const std::wstring& String::getRaw() const {
        return _raw;
    }


    std::wostream& operator<<(std::wostream& out, Ptr<String> string) {
        if (string) {
            out << string->getRaw();
        } else {
            out << L"null";
        }
        return out;
    }
}