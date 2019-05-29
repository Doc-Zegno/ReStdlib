#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "ArrayList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
	TEST_CLASS(ArrayListSliceTest) {
	private:
		Ptr<List<Int>> numbers = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
		Ptr<List<Int>> evens = numbers->getSlice(1, 10, 2);
		Ptr<List<Int>> odds = numbers->getSlice(0, 10, 2);
		Ptr<List<Int>> empty = numbers->getSlice(10, 10, 1);
		Ptr<List<Int>> one = numbers->getSlice(0, 1, 1);

	public:
		TEST_METHOD(ToString) {
			Assert::AreEqual(L"[]", empty->toString()->getRaw().c_str());
			Assert::AreEqual(L"[1]", one->toString()->getRaw().c_str());
			Assert::AreEqual(L"[2, 4, 6, 8, 10]", evens->toString()->getRaw().c_str());
			Assert::AreEqual(L"[1, 3, 5, 7, 9]", odds->toString()->getRaw().c_str());
		}


		TEST_METHOD(GetRest) {
			Assert::AreEqual(L"[3, 5, 7, 9]", odds->getRest()->toString()->getRaw().c_str());

			// Must throw for empty
			auto test = [this]() {
				empty->getRest();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(GetFirst) {
			Assert::AreEqual(Int(2), evens->getFirst());

			// Empty must throw
			auto test = [this]() {
				empty->getFirst();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(GetLast) {
			Assert::AreEqual(Int(10), evens->getLast());

			// Empty must throw
			auto test = [this]() {
				empty->getLast();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(Get) {
			Assert::AreEqual(Int(5), odds->get(2));
			Assert::AreEqual(Int(3), odds->get(-4));

			// Out of range
			auto test = [this]() {
				odds->get(5);
			};
			Assert::ExpectException<IndexError>(test);
		}


		TEST_METHOD(SkipAndTake) {
			// Skip and take
			Assert::AreEqual(L"[2, 4, 6, 8]", evens->take(4)->toString()->getRaw().c_str());
			Assert::AreEqual(L"[10]", evens->skip(4)->toString()->getRaw().c_str());

			// Skip and take (too much)
			Assert::AreEqual(L"[1, 3, 5, 7, 9]", odds->take(100)->toString()->getRaw().c_str());
			Assert::AreEqual(L"[]", odds->skip(100)->toString()->getRaw().c_str());

			// Skip and take (too few)
			Assert::AreEqual(L"[]", evens->take(0)->toString()->getRaw().c_str());
			Assert::AreEqual(L"[2, 4, 6, 8, 10]", evens->skip(0)->toString()->getRaw().c_str());
		}


		TEST_METHOD(GetSlice) {
			Assert::AreEqual(L"[4, 8]", evens->getSlice(1, -1, 2)->toString()->getRaw().c_str());
			Assert::AreEqual(L"[]", odds->getSlice(5, 5, 1)->toString()->getRaw().c_str());
		}


		TEST_METHOD(LengthAndEmptyness) {
			Assert::AreEqual(Bool(true), evens->getHasLength());
			Assert::AreEqual(Int(5), evens->getLength());
			Assert::AreEqual(Bool(false), evens->getIsEmpty());

			// The same for empty one
			Assert::AreEqual(Bool(true), empty->getIsEmpty());
			Assert::AreEqual(Int(0), empty->getLength());
		}


		TEST_METHOD(Set) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto evens = mutableList->getMutableSlice(1, 10, 2);
			evens->set(0, Int(-2));
			Assert::AreEqual(L"[-2, 4, 6, 8, 10]", evens->toString()->getRaw().c_str());
		}


		TEST_METHOD(Add) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto evens = mutableList->getMutableSlice(1, 10, 2);
			
			auto test = [evens]() {
				evens->add(12);
			};
			Assert::ExpectException<NotSupportedError>(test);
		}


		TEST_METHOD(AddAll) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto evens = mutableList->getMutableSlice(1, 10, 2);

			auto test = [evens]() {
				evens->addAll(makeList({ 11, 12, 13 }));
			};
			Assert::ExpectException<NotSupportedError>(test);
		}


		TEST_METHOD(InsertAt) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto evens = mutableList->getMutableSlice(1, 10, 2);

			auto test = [evens]() {
				evens->insertAt(0, 137);
			};
			Assert::ExpectException<NotSupportedError>(test);
		}


		TEST_METHOD(RemoveAt) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto evens = mutableList->getMutableSlice(1, 10, 2);

			auto test = [evens]() {
				evens->removeAt(0);
			};
			Assert::ExpectException<NotSupportedError>(test);
		}


		TEST_METHOD(Resize) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto evens = mutableList->getMutableSlice(1, 10, 2);

			auto test = [evens]() {
				evens->resize(5);
			};
			Assert::ExpectException<NotSupportedError>(test);
		}


		TEST_METHOD(Clear) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
			auto evens = mutableList->getMutableSlice(1, 10, 2);

			auto test = [evens]() {
				evens->clear();
			};
			Assert::ExpectException<NotSupportedError>(test);
		}
	};
}
