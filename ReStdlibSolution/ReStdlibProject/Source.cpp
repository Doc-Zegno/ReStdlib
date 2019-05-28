#include <iostream>
#include <conio.h>

#include "Errors.h"
#include "ArrayList.h"
#include "HashSet.h"
#include "HashMap.h"
#include "Range.h"
#include "BasicString.h"
#include "Print.h"
#include "BoxedPrimitives.h"

using namespace ReLang;


class SquareFunction : public Function<Int, Int> {
public:
    virtual Int operator()(Int x) override {
        return x * x;
    }
};


class ToSeriesFunction : public Function<Ptr<ArrayList<Int>>, Int> {
public:
    virtual Ptr<ArrayList<Int>> operator()(Int x) override {
        return makePtr<ArrayList<Int>>({ x, x * x, x * x * x });
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


class IdentityComparator : public Function<Bool, Int, Int> {
public:
    virtual Bool operator()(Int x, Int y) override {
        return x <= y;
    }
};


class SecondValueKey : public Function<Int, Tuple<Ptr<String>, Int>> {
public:
    virtual Int operator()(Tuple<Ptr<String>, Int> x) override {
        return x.getSecond();
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

        auto mess = Ptr<ArrayList<Int>>(new ArrayList<Int>({ 3, 4, 1, 7, 2, 6, 5 }));
        auto messPairs = Ptr<ArrayList<Tuple<Ptr<String>, Int>>>(
            new ArrayList<Tuple<Ptr<String>, Int>>{
                Tuple<Ptr<String>, Int>(makePtr<String>(L"Hello World"), 3),
                Tuple<Ptr<String>, Int>(makePtr<String>(L"Sample Text"), 1),
                Tuple<Ptr<String>, Int>(makePtr<String>(L"Serious Arguments"), 2),
            });
        printAll(L"Unsorted:", mess);
        printAll(L"Sorted:", mess->sortWith(Ptr<Function<Bool, Int, Int>>(new IdentityComparator())));
        printAll(L"Sorted:", mess->sort(false));
        printAll(L"Unsorted Pairs:", messPairs);
        printAll(L"Sorted Pairs:", messPairs->sortBy(Ptr<Function<Int, Tuple<Ptr<String>, Int>>>(new SecondValueKey()), false));
        printAll(L"Mess.max():", mess->max());
        printAll(L"Mess.min():", mess->min());
        printAll(L"MessPairs.maxBy():", messPairs->maxBy(Ptr<Function<Int, Tuple<Ptr<String>, Int>>>(new SecondValueKey())));
        printAll(L"MessPairs.minBy():", messPairs->minBy(Ptr<Function<Int, Tuple<Ptr<String>, Int>>>(new SecondValueKey())));

        auto consed = mess->cons(Int(8))->cons(Int(10))->cons(Int(9));
        auto extended = consed->cons(Int(11));
        printAll(L"Cons(9, 10, 8, mess):", consed);
        printAll(L"Cons(11, consed):", extended);
        printAll(L"Sorted extended:", extended->sort());
        printAll(L"Extended.length:", extended->getLength());

        auto matrix = makePtr<ArrayList<Ptr<ArrayList<Int>>>>({
            makePtr<ArrayList<Int>>({ 0 }),
            makePtr<ArrayList<Int>>(),
            makePtr<ArrayList<Int>>({ 1, 2, 3 }),
            makePtr<ArrayList<Int>>({ 4, 5, 6, 7 }),
            makePtr<ArrayList<Int>>({ 8, 9 })
        });

        printAll(L"Matrix:", matrix);
        printAll(L"Matrix.flatten():", matrix->flatten<Int>());
        printAll(L"List.take(3).flatMap():", list->take(3)->flatMap<Int>(Ptr<Function<Ptr<ArrayList<Int>>, Int>>(new ToSeriesFunction())));
        printAll(L"List.groupBy2():", list->groupBy2());
        printAll(L"List.chainBy2():", list->chainBy2());

        matrix->get(0)->insertAt(-1, Int(1));
        matrix->get(1)->resize(5);
        matrix->get(2)->add(Int(2));
        matrix->get(2)->removeAt(1);
        matrix->get(3)->addAll(makePtr<ArrayList<Int>>({ 6, 5, 4 }));
        matrix->get(4)->clear();
        printAll(L"Matrix:", matrix);

        auto xs = makePtr<ArrayList<Int>>({ 1, 2, 3, 4, 5 });
        auto ys = makePtr<ArrayList<Int>>({ 1, 2, 3, 4, 6 });
        auto zs = makePtr<ArrayList<Int>>({ 1, 2, 3, 4, 5, 6 });
        auto ws = makePtr<ArrayList<Int>>({ 1, 2, 3, 4, 5 });
        printAll(L"xs == xs:", xs == xs);
        printAll(L"xs == ys:", xs == ys);
        printAll(L"xs == zs:", xs == zs);
        printAll(L"xs == ws:", xs == ws);

        auto set = makePtr<HashSet<Int>>({ 1, 2, 3, 1, 2, 4, 5, 6, 6, 7, 4 });
        auto anotherSet = makePtr<HashSet<Int>>({ 1, 3, 5, 7, 9, 11 });
        printAll(L"Set:", set);
        printAll(L"Another set:", anotherSet);
        printAll(L"Union:", set->unioned(anotherSet));
        printAll(L"Intersection:", set->intersection(anotherSet));
        printAll(L"Difference:", set->difference(anotherSet));
        set->add(Int(11));
        printAll(L"Add:", set);
        set->addAll(list);
        printAll(L"AddAll:", set);
        set->remove(Int(1));
        printAll(L"Remove:", set);
        set->removeAll(list);
        printAll(L"RemoveAll:", set);

        auto map = makePtr<HashMap<Int, Int>>({ Tuple<Int, Int>(1, 2), Tuple<Int, Int>(3, 4), Tuple<Int, Int>(5, 6) });
        printAll(L"Map:", map);
		printAll(L"Map.keys:", map->getKeys());
		printAll(L"Map.values:", map->getValues());

		printAll(L"Boxed numbers:", boxIterable(list));
		std::wcout << list << std::endl;

        print(list->get(10));
    } catch (IndexError& e) {
        print(e.getMessage());
    }

    auto ch = _getch();
}

