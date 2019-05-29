#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "BoxedPrimitives.h"
#include "ArrayList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
    TEST_CLASS(IterableTest) {
    private:
        class SquareFunction : public Function<Int, Int> {
        public:
            virtual Int operator()(Int x) override {
                return x * x;
            }
        };


        class SumTwoIntsReducer : public Function<Int, Int, Int> {
        public:
            virtual Int operator()(Int x, Int y) override {
                return x + y;
            }
        };


        class ToSeriesFunction : public Function<Ptr<ArrayList<Int>>, Int> {
        public:
            virtual Ptr<ArrayList<Int>> operator()(Int x) override {
                return makePtr<ArrayList<Int>>({ x, x * x, x * x * x });
            }
        };


    public:
		TEST_METHOD(GetIndices) {
			auto numbers = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto indices = numbers->getIndices();
			Assert::AreEqual(Bool(true), indices->getHasLength());
			Assert::AreEqual(Int(10), indices->getLength());
			Assert::AreEqual(Bool(false), indices->getIsEmpty());
			Assert::AreEqual(L"[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]", makeList<Int>(indices)->toString()->getRaw().c_str());
		}


		TEST_METHOD(Enumerate) {
			auto strings = makeList({
				makeStr(L"Hello, World!"),
				Ptr<String>(),
				makeStr(L"Sample Text"),
				makeStr(L"Serious Arguments")
			});

			auto enumerate = strings->enumerate();
			Assert::AreEqual(Bool(true), enumerate->getHasLength());
			Assert::AreEqual(Int(4), enumerate->getLength());
			Assert::AreEqual(Bool(false), enumerate->getIsEmpty());
			Assert::AreEqual(L"(0, Hello, World!)::(1, null)::(2, Sample Text)::(3, Serious Arguments)::[]", enumerate->toString()->getRaw().c_str());
		}


		TEST_METHOD(Zip) {
			auto numbers = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto strings = makeList({
				makeStr(L"Hello, World!"),
				Ptr<String>(),
				makeStr(L"Sample Text"),
				makeStr(L"Serious Arguments")
			});

			auto zipped = zip(strings, numbers);
			Assert::AreEqual(Bool(true), zipped->getHasLength());
			Assert::AreEqual(Int(4), zipped->getLength());
			Assert::AreEqual(Bool(false), zipped->getIsEmpty());
			Assert::AreEqual(L"(Hello, World!, 1)::(null, 2)::(Sample Text, 3)::(Serious Arguments, 4)::[]", zipped->toString()->getRaw().c_str());
		}


		TEST_METHOD(Map) {
			auto numbers = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto mapping = makeFunc<SquareFunction>();
			auto mapped = numbers->map(mapping);
			Assert::AreEqual(Bool(true), mapped->getHasLength());
			Assert::AreEqual(Int(10), mapped->getLength());
			Assert::AreEqual(Bool(false), mapped->getIsEmpty());
			Assert::AreEqual(L"1::4::9::16::25::36::49::64::81::100::[]", mapped->toString()->getRaw().c_str());
		}


		TEST_METHOD(MaxAndMin) {
			auto messed = makeList({ 3, 4, 1, 7, 2, 6, 5 });
			auto tuple1 = messed->max();
			Assert::AreEqual(7, tuple1.getFirst());
			Assert::AreEqual(3, tuple1.getSecond());
			auto tuple2 = messed->min();
			Assert::AreEqual(1, tuple2.getFirst());
			Assert::AreEqual(2, tuple2.getSecond());
		}


		TEST_METHOD(Sort) {
			auto messed = makeList({ 3, 4, 1, 7, 2, 6, 5 });
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7]", messed->sort()->toString()->getRaw().c_str());
			Assert::AreEqual(L"[7, 6, 5, 4, 3, 2, 1]", messed->sort(false)->toString()->getRaw().c_str());
		}


		TEST_METHOD(Cons) {
			auto messed = makeList({ 3, 4, 1, 7, 2, 6, 5 });
			auto consed = messed->cons(Int(8))->cons(Int(9));
			Assert::AreEqual(L"9::8::3::4::1::7::2::6::5::[]", consed->toString()->getRaw().c_str());
			Assert::AreEqual(L"1::2::3::4::5::6::7::8::9::[]", consed->sort()->toString()->getRaw().c_str());
			Assert::AreEqual(Int(9), consed->getLength());
		}


		TEST_METHOD(Flatten) {
			auto matrix = makeList({
				makeList({ 0 }),
				makeList<Int>(),
				makeList({ 1, 2, 3 }),
				makeList({ 4, 5, 6, 7 }),
				makeList({ 8, 9 })
			});
			Assert::AreEqual(L"0::1::2::3::4::5::6::7::8::9::[]", matrix->flatten<Int>()->toString()->getRaw().c_str());
		}


		TEST_METHOD(FlatMap) {
			auto numbers = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto flatMapped = numbers->take(3)->flatMap<Int>(makeFunc<ToSeriesFunction>());
			Assert::AreEqual(L"1::1::1::2::4::8::3::9::27::[]", flatMapped->toString()->getRaw().c_str());
		}


		TEST_METHOD(GroupBy2) {
			auto numbers = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

			auto grouped = numbers->take(7)->groupBy2();
			Assert::AreEqual(Int(3), grouped->getLength());
			Assert::AreEqual(L"(1, 2)::(3, 4)::(5, 6)::[]", grouped->toString()->getRaw().c_str());

			auto emptyGrouped = numbers->take(1)->groupBy2();
			Assert::IsTrue(emptyGrouped->getIsEmpty());
			Assert::AreEqual(Int(0), emptyGrouped->getLength());
		}


		TEST_METHOD(ChainBy2) {
			auto numbers = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

			auto chained = numbers->take(5)->chainBy2();
			Assert::AreEqual(Int(4), chained->getLength());
			Assert::AreEqual(L"(1, 2)::(2, 3)::(3, 4)::(4, 5)::[]", chained->toString()->getRaw().c_str());

			auto emptyChained = numbers->take(1)->chainBy2();
			Assert::IsTrue(emptyChained->getIsEmpty());
			Assert::AreEqual(Int(0), emptyChained->getLength());
		}


		TEST_METHOD(BoxIterable) {
			auto numbers = makeList({ 1, 2, 3, 4, 5 });
			Assert::AreEqual(L"1::2::3::4::5::[]", boxIterable(numbers)->toString()->getRaw().c_str());
		}


		TEST_METHOD(ZipInPlace) {
			// Zipping in place
			auto xs = makeList({ 1, 2, 3, 4, 5 });
			auto ys = makeList({ 11, 12, 13, 14, 15 });
			xs->zipInPlace(ys, makeFunc<SumTwoIntsReducer>());
			Assert::AreEqual(L"[12, 14, 16, 18, 20]", xs->toString()->getRaw().c_str());
		}


		TEST_METHOD(SortInPlace) {
			auto mess = makeList({ 3, 4, 1, 5, 2 });
			mess->sortInPlace();
			Assert::AreEqual(L"[1, 2, 3, 4, 5]", mess->toString()->getRaw().c_str());
		}
    };
}