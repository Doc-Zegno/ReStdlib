#include <iostream>
#include <conio.h>

#include "Errors.h"
#include "ArrayList.h"
#include "BasicString.h"

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
        std::wcout << x << std::endl;
    }
};


class SumTwoIntsReducer : public Function<Int, Int, Int> {
public:
    virtual Int operator()(Int x, Int y) override {
        return x + y;
    }
};


void printIterable(Ptr<Iterable<Int>> iterable) {
    std::wcout << iterable->toString() << std::endl;
}


void printIterable(Ptr<Iterable<Ptr<String>>> iterable) {
    std::wcout << iterable->toString() << std::endl;
}


int main() {
    auto list = Ptr<List<Int>>(new ArrayList<Int>({ 1, 2, 3, 4, 5 }));
    auto strings = Ptr<List<Ptr<String>>>(
        new ArrayList<Ptr<String>>(
            { 
                Ptr<String>(new String(L"Hello, World!")), 
                Ptr<String>(new String(L"Sample Text")), 
                Ptr<String>(new String(L"Serious Arguments")) 
            }));

    printIterable(strings);
    std::wcout << std::boolalpha;
    std::wcout << L"Has length: " << strings->getHasLength() << std::endl;
    std::wcout << L"Lenght: " << strings->getLength() << std::endl;
    std::wcout << L"First: " << strings->getFirst() << std::endl;
    std::wcout << L"Last: " << strings->getLast() << std::endl;
    auto rest = strings->getRest();
    std::wcout << L"Rest: ";
    printIterable(rest);
    std::wcout << L"Rest once again: ";
    printIterable(rest);

    printIterable(list);
    std::wcout << "Take 3: ";
    printIterable(list->take(3));
    std::wcout << "Skip 2: ";
    printIterable(list->skip(2));
    printIterable(list->map(Ptr<Function<Int, Int>>(new SquareFunction())));
    printIterable(list->filter(Ptr<Function<Bool, Int>>(new IsOddFunction())));
    std::wcout << "For each:\n";
    list->forEach(Ptr<Function<Void, Int>>(new PrintIntAction()));
    std::wcout << "Sum: " << list->reduce(Ptr<Function<Int, Int, Int>>(new SumTwoIntsReducer())) << std::endl;

    try {
        std::wcout << list->get(5);
    } catch (IndexError& e) {
        std::wcout << e.getMessage() << std::endl;
    }

    auto ch = _getch();
}

