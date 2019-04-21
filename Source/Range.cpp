#include "Range.h"

#include <algorithm>

#include "BasicString.h"
#include "Utils/IterableUtils.h"


namespace ReLang {
    class RangeIterator : public Iterator<Int> {
    private:
        Int _index;
        Int _end;
        Int _step;

    public:
        RangeIterator(Int index, Int end, Int step);

        virtual Int getCurrent() override;
        virtual Bool moveNext() override;
        virtual Ptr<Iterator<Int>> clone() override;
    };


    RangeIterator::RangeIterator(Int index, Int end, Int step)
        : _index(index), _end(end), _step(step)
    {
    }


    Int RangeIterator::getCurrent() {
        return _index;
    }


    Bool RangeIterator::moveNext() {
        _index += _step;
        if (_index < _end) {
            return true;
        } else {
            _index = _end;
            return false;
        }
    }


    Ptr<Iterator<Int>> RangeIterator::clone() {
        return Ptr<Iterator<Int>>(new RangeIterator(_index, _end, _step));
    }



    // R a n g e
    Range::Range(Int start, Int end, Int step) : _start(start), _end(end), _step(step), _length((_end - _start + _step - 1) / _step) {
    }


    Int Range::getStart() {
        return _start;
    }


    Int Range::getEnd() {
        return _end;
    }


    Int Range::getStep() {
        return _step;
    }


    Ptr<Iterator<Int>> Range::getIterator() {
        return Ptr<Iterator<Int>>(new RangeIterator(_start - _step, _end, _step));
    }


    Int Range::get(Int index) {
        auto translatedIndex = Utils::translateIndex(index, _length);
        return _start + translatedIndex * _step;
    }


    Ptr<List<Int>> Range::getSlice(Int start, Int end, Int step) {
        auto translatedStart = start == _length ? start : Utils::translateIndex(start, _length);
        auto translatedEnd = end == _length ? end : Utils::translateIndex(end, _length);
        if (translatedEnd < translatedStart) {
            translatedEnd = translatedStart;
        }
        return Ptr<List<Int>>(new Range(_start + translatedStart * _step, _start + translatedEnd * _step, _step * step));
    }


    Ptr<Iterable<Int>> Range::take(Int number) {
        if (number >= 0) {
            auto translatedNumber = std::min(number, _length);  // Can't take more than actually exist
            return getSlice(0, translatedNumber, 1);
        } else {
            throw ValueError(L"Number of taken items should be non-negative");
        }
    }


    Ptr<Iterable<Int>> Range::skip(Int number) {
        if (number >= 0) {
            auto translatedNumber = std::min(number, _length);  // Can't skip more than actually exist
            return getSlice(translatedNumber, _length, 1);
        } else {
            throw ValueError(L"Number of skipped items should be non-negative");
        }
    }


    Int Range::getFirst() {
        if (_length > 0) {
            return _start;
        } else {
            throw EmptyIterableError();
        }
    }


    Int Range::getLast() {
        if (_length > 0) {
            auto lastIndex = _length - 1;
            return _start + lastIndex * _step;
        } else {
            throw EmptyIterableError();
        }
    }


    Ptr<Iterable<Int>> Range::getRest() {
        if (_length > 0) {
            return getSlice(1, _length, 1);
        } else {
            throw EmptyIterableError();
        }
    }


    Bool Range::getIsEmpty() {
        return _length == 0;
    }


    Bool Range::getHasLength() {
        return true;
    }


    Int Range::getLength() {
        return _length;
    }


    Ptr<Iterable<Int>> Range::getSelf() {
        return shared_from_this();
    }


    Ptr<String> Range::toString() {
        auto representation =
            std::wstring(L"Range(start=")
            + std::to_wstring(_start)
            + L", end="
            + std::to_wstring(_end)
            + L", step="
            + std::to_wstring(_step)
            + L")";
        return makePtr<String>(std::move(representation));
    }
}
