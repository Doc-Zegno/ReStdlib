#pragma once

#include "List.h"


namespace ReLang {
    class Range : public List<Int>, public EnableSelf<Range> {
    private:
        Int _start;
        Int _end;
        Int _step;
        Int _length;

    public:
        Range(Int start, Int end, Int step = 1);

        Int getStart();
        Int getEnd();
        Int getStep();

        virtual Ptr<Iterator<Int>> getIterator() override;
        virtual Int get(Int index) override;
        virtual Ptr<List<Int>> getSlice(Int start, Int end, Int step) override;
        virtual Ptr<Iterable<Int>> getIndices() override;
        virtual Ptr<Iterable<Int>> take(Int number) override;
        virtual Ptr<Iterable<Int>> skip(Int number) override;
        virtual Int getFirst() override;
        virtual Int getLast() override;
        virtual Ptr<Iterable<Int>> getRest() override;
        virtual Bool getIsEmpty() override;
        virtual Bool getHasLength() override;
        virtual Int getLength() override;
        virtual Ptr<Iterable<Int>> getSelf() override;
        virtual Ptr<String> toString() override;
    };
}
