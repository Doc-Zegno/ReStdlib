#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "ArrayList.h"
#include "Range.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
    TEST_CLASS(RangeTest) {
	private:
		Ptr<Range> empty = makePtr<Range>(0, 0, 1);
		Ptr<Range> numbers = makePtr<Range>(1, 11, 1);

    public:
		TEST_METHOD(ToString) {
			Assert::AreEqual(L"[]", makePtr<ArrayList<Int>>(empty)->toString()->getRaw().c_str());
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers)->toString()->getRaw().c_str());
		}


		TEST_METHOD(GetRest) {
			Assert::AreEqual(L"[2, 3, 4, 5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers->getRest())->toString()->getRaw().c_str());

			// Empty must throw
			auto test = [this]() {
				empty->getRest();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(GetFirst) {
			Assert::AreEqual(Int(1), numbers->getFirst());
			
			// Empty must throw
			auto test = [this]() {
				empty->getFirst();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(GetLast) {
			Assert::AreEqual(Int(10), numbers->getLast());

			// Empty must throw
			auto test = [this]() {
				empty->getLast();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(Get) {
			Assert::AreEqual(Int(3), numbers->get(2));
			Assert::AreEqual(Int(7), numbers->get(-4));

			// Out of range
			auto testOutOfRange = [this]() {
				numbers->get(10);
			};
			Assert::ExpectException<IndexError>(testOutOfRange);

			// Empty must throw
			auto testEmpty = [this]() {
				empty->get(0);
			};
			Assert::ExpectException<IndexError>(testEmpty);
		}


		TEST_METHOD(SkipAndTake) {
			// Skip and take
			Assert::AreEqual(L"[1, 2, 3, 4]", makePtr<ArrayList<Int>>(numbers->take(4))->toString()->getRaw().c_str());
			Assert::AreEqual(L"[5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers->skip(4))->toString()->getRaw().c_str());

			// Skip and take (too much)
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers->take(100))->toString()->getRaw().c_str());
			Assert::AreEqual(L"[]", makePtr<ArrayList<Int>>(numbers->skip(100))->toString()->getRaw().c_str());

			// Skip and take (too few)
			Assert::AreEqual(L"[]", makePtr<ArrayList<Int>>(numbers->take(0))->toString()->getRaw().c_str());
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers->skip(0))->toString()->getRaw().c_str());
		}


		TEST_METHOD(GetSlice) {
			Assert::AreEqual(L"[2, 4, 6, 8]", makePtr<ArrayList<Int>>(numbers->getSlice(1, -1, 2))->toString()->getRaw().c_str());
			Assert::AreEqual(L"[]", makePtr<ArrayList<Int>>(numbers->getSlice(10, 10, 1))->toString()->getRaw().c_str());
		}


		TEST_METHOD(LengthAndEmpty) {
			Assert::AreEqual(Bool(true), numbers->getHasLength());
			Assert::AreEqual(Int(10), numbers->getLength());
			Assert::AreEqual(Bool(false), numbers->getIsEmpty());

			Assert::AreEqual(Bool(true), empty->getIsEmpty());
			Assert::AreEqual(Int(0), empty->getLength());
		}


		TEST_METHOD(Contains) {
			// Contiguous
			for (auto i = 1; i <= 10; i++) {
				Assert::IsTrue(numbers->contains(i));
			}
			Assert::IsFalse(numbers->contains(0));
			Assert::IsFalse(numbers->contains(11));

			// Sparse
			auto each3 = staticPointerCast<Range>(numbers->getSlice(1, -1, 3));  // [2, 5, 8]
			for (auto i = 2; i < 10; i += 3) {
				Assert::IsTrue(each3->contains(i));
				Assert::IsFalse(each3->contains(i + 1));
				Assert::IsFalse(each3->contains(i + 2));
			}
			Assert::IsFalse(each3->contains(1));
			Assert::IsFalse(each3->contains(11));
		}
    };
}