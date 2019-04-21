#include <iostream>
#include <conio.h>

#include "Errors.h"
#include "ArrayList.h"
#include "Range.h"
#include "BasicString.h"
#include "Print.h"

using namespace ReLang;


class SquareFunction : public Function<Int, Int> {
public:
    virtual Int operator()(Int x) override {
        return x * x;
    }
};


class IsOddFunction : public Function<Bool, Int> {
public:
    virtual Bool operator()(Int x) override {
        return x % 2 == 1;
    }
};


class PrintIntAction : public Function<Void, Int> {
public:
    virtual Void operator()(Int x) override {
        print(x);
    }
};


class SumTwoIntsReducer : public Function<Int, Int, Int> {
public:
    virtual Int operator()(Int x, Int y) override {
        return x + y;
    }
};


int main() {
    auto list = Ptr<List<Int>>(new ArrayList<Int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
    auto strings = Ptr<List<Ptr<String>>>(
        new ArrayList<Ptr<String>>(
            { 
                Ptr<String>(new String(L"Hello, World!")), 
                Ptr<String>(),
                Ptr<String>(new String(L"Sample Text")), 
                Ptr<String>(new String(L"Serious Arguments")) 
            }));

    std::wcout << std::boolalpha;
    printAll(L"Strings:", strings);
    printAll(L"Enumerated:", strings->enumerate());
    printAll(L"Has length:", strings->getHasLength());
    printAll(L"Lenght:", strings->getLength());
    printAll(L"First:", strings->getFirst());
    printAll(L"Last:", strings->getLast());
    auto rest = strings->getRest();
    printAll(L"Rest:", rest);
    printAll(L"Rest once again:", rest);

    printAll(L"Numbers:", list);
    printAll(L"Take 3:", list->take(3));
    printAll(L"Skip 2:", list->skip(2));
    auto squares = list->map(Ptr<Function<Int, Int>>(new SquareFunction()));
    printAll(L"Squares:", squares);
    printAll(L"Odds:", list->filter(Ptr<Function<Bool, Int>>(new IsOddFunction())));
    print(L"For each:");
    list->forEach(Ptr<Function<Void, Int>>(new PrintIntAction()));
    printAll(L"Sum:", list->reduce(Ptr<Function<Int, Int, Int>>(new SumTwoIntsReducer())));

    printAll(L"Zip:", zip(strings, squares));
    printAll(L"Enumerated Zip:", zip(strings, squares)->enumerate());

    try {
        printAll(L"List[1] =", list->get(1));
        printAll(L"List[-1] =", list->get(-1));
        auto slice = list->getSlice(1, 10, 2);
        printAll(L"Slice =", slice);
        printAll(L"Slice.length =", slice->getLength());
        printAll(L"Slice[0] =", slice->get(0));
        printAll(L"Slice[-1] =", slice->get(-1));
        auto nestedSlice = slice->getSlice(0, 5, 2);
        printAll(L"Nested slice =", nestedSlice);
        printAll(L"Nested slice[1] =", nestedSlice->get(1));
        printAll(L"Nested slice[-2] =", nestedSlice->get(-2));

        auto string = strings->get(0);
        printAll(L"String:", string);
        printAll(L"String[1:9:2]:", string->getSlice(1, 9, 2));
        printAll(L"String.take(5):", string->take(5));
        printAll(L"String.take(20):", string->take(20));
        printAll(L"String.skip(3):", string->skip(3));
        printAll(L"String.skip(20):", string->skip(20));
        printAll(L"String.rest:", string->getRest());
        printAll(L"List[1:-1]:", list->getSlice(1, -1, 1));
        printAll(L"Strings.indices:", strings->getIndices());

        auto range = makePtr<Range>(0, 10, 2);
        printAll(L"Range(0, 10, 2):", range);
        printAll(L"Range:", makePtr<ArrayList<Int>>(range));
        printAll(L"Range[::2]:", makePtr<ArrayList<Int>>(range->getSlice(0, 5, 2)));
        printAll(L"Range.rest:", makePtr<ArrayList<Int>>(range->getRest()));
        print(list->get(10));
    } catch (IndexError& e) {
        print(e.getMessage());
    }

    auto ch = _getch();
}

