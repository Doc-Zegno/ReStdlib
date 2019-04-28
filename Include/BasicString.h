#pragma once

#include <string>
#include <iostream>

#include "List.h"


namespace ReLang {
    class String : public List<Char>, public EnableSelf<String>, public Equatable<String> {
    private:
        std::wstring _raw;

    public:
        String(const Char* string);
        String(const std::wstring& string);
        String(std::wstring&& string);
        String(Int count, Char character);

        
        virtual Ptr<Iterable<Char>> getSelf() override;

        virtual Ptr<Iterator<Char>> getIterator() override;

        virtual Ptr<Iterable<Char>> take(Int number) override;

        virtual Ptr<Iterable<Char>> skip(Int number) override;

        virtual Char getFirst() override;

        virtual Char getLast() override;

        virtual Ptr<Iterable<Char>> getRest() override;

        virtual Bool getIsEmpty();

        virtual Int getLength() override;

        virtual Bool getHasLength() override;

        virtual Char get(Int index) override;

        virtual Ptr<List<Char>> getSlice(Int start, Int end, Int step) override;

        inline Ptr<Iterable<Int>> getIndices() override;

        virtual Bool operator==(Ptr<String> other) override;

        virtual Ptr<String> toString() override;

        Char operator[](Int index);

        const std::wstring& getRaw() const;
    };


    std::wostream& operator<<(std::wostream& out, Ptr<String> string);
}
