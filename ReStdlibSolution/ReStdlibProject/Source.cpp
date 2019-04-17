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
    printIterable(list->map(Ptr<Function<Int, Int>>(new SquareFunction())));
    printIterable(list->filter(Ptr<Function<Bool, Int>>(new IsOddFunction())));

    try {
        std::wcout << list->get(5);
    } catch (IndexError& e) {
        std::wcout << e.getMessage() << std::endl;
    }

    auto ch = _getch();
}

