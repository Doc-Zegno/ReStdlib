#include <iostream>
#include <conio.h>

#include "ArrayList.h"

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
    auto iterator = iterable->getIterator();
    while (iterator->moveNext()) {
        std::cout << iterator->getCurrent() << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    auto list = Ptr<Iterable<Int>>(new ArrayList<Int>({ 1, 2, 3, 4, 5 }));
    printIterable(list);
    printIterable(list->map(Ptr<Function<Int, Int>>(new SquareFunction())));
    printIterable(list->filter(Ptr<Function<Bool, Int>>(new IsOddFunction())));
    auto ch = _getch();
}

