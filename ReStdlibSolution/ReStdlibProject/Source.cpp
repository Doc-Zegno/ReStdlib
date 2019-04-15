#include <iostream>
#include <conio.h>

#include "Errors.h"
#include "ArrayList.h"
#include "BasicString.h"

using namespace ReLang;


class SquareFunction : public Function<Int, Int> {
public:
    virtual Int __call__(Int x) override {
        return x * x;
    }
};


class IsOddFunction : public Function<Bool, Int> {
public:
    virtual Bool __call__(Int x) override {
        return x % 2 == 1;
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
    auto strings = Ptr<List<Ptr<String>>>(new ArrayList<Ptr<String>>({ Ptr<String>(new String(L"Sample Text")), Ptr<String>(new String(L"Serious Arguments")) }));
    printIterable(strings);
    printIterable(list);
    printIterable(list->map(Ptr<Function<Int, Int>>(new SquareFunction())));
    printIterable(list->filter(Ptr<Function<Bool, Int>>(new IsOddFunction())));

    try {
        std::wcout << list->__get__(5);
    } catch (IndexError& e) {
        std::wcout << e.getMessage() << std::endl;
    }

    auto ch = _getch();
}

