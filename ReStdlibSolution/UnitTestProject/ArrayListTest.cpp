#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "ArrayList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {		
	TEST_CLASS(ArrayListTest) {
	private:
		Ptr<List<Int>> empty = makeList<Int>();
		Ptr<List<Int>> repeating = makeList<Int>(5, 2);
		Ptr<List<Int>> copy = makeList<Int>(repeating);
		Ptr<List<Int>> numbers = makeList({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

	public:
		TEST_METHOD(ToString) {
			Assert::AreEqual(L"[]", empty->toString()->getRaw().c_str());
			Assert::AreEqual(L"[2, 2, 2, 2, 2]", repeating->toString()->getRaw().c_str());
			Assert::AreEqual(L"[2, 2, 2, 2, 2]", copy->toString()->getRaw().c_str());
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", numbers->toString()->getRaw().c_str());
		}


		TEST_METHOD(GetRest) {
			Assert::AreEqual(L"[2, 3, 4, 5, 6, 7, 8, 9, 10]", numbers->getRest()->toString()->getRaw().c_str());

			auto test = [this]() {
				empty->getRest();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(GetFirst) {
			Assert::AreEqual(Int(1), numbers->getFirst());

			auto testFirst = [this]() {
				empty->getFirst();
			};
			Assert::ExpectException<EmptyIterableError>(testFirst);
		}


		TEST_METHOD(GetLast) {
			Assert::AreEqual(Int(10), numbers->getLast());

			auto testLast = [this]() {
				empty->getLast();
			};
			Assert::ExpectException<EmptyIterableError>(testLast);
		}


		TEST_METHOD(Get) {
			// Get (successful)
			Assert::AreEqual(Int(3), numbers->get(2));
			Assert::AreEqual(Int(7), numbers->get(-4));

			// Get (out of range)
			auto testOutOfRange = [this]() {
				numbers->get(10);
			};
			Assert::ExpectException<IndexError>(testOutOfRange);

			// Get (empty must throw)
			auto testEmpty = [this]() {
				empty->get(0);
			};
			Assert::ExpectException<IndexError>(testEmpty);
		}


		TEST_METHOD(SkipAndTake) {
			// Skip and take
			Assert::AreEqual(L"[1, 2, 3, 4]", numbers->take(4)->toString()->getRaw().c_str());
			Assert::AreEqual(L"[5, 6, 7, 8, 9, 10]", numbers->skip(4)->toString()->getRaw().c_str());

			// Skip and take (too much)
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", numbers->take(100)->toString()->getRaw().c_str());
			Assert::AreEqual(L"[]", numbers->skip(100)->toString()->getRaw().c_str());

			// Skip and take (too few)
			Assert::AreEqual(L"[]", numbers->take(0)->toString()->getRaw().c_str());
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", numbers->skip(0)->toString()->getRaw().c_str());
		}


		TEST_METHOD(GetSlice) {
			// Slice
			Assert::AreEqual(L"[2, 4, 6, 8]", numbers->getSlice(1, -1, 2)->toString()->getRaw().c_str());
			Assert::AreEqual(L"[]", numbers->getSlice(10, 10, 1)->toString()->getRaw().c_str());

			// Slice (out of range)
			auto testOutOfRange = [this]() {
				numbers->getSlice(11, 11, 1);
			};
			Assert::ExpectException<IndexError>(testOutOfRange);
		}


		TEST_METHOD(GetLengthAndEmpty) {
			// Length and emptyness
			Assert::AreEqual(Bool(true), numbers->getHasLength());
			Assert::AreEqual(Int(10), numbers->getLength());
			Assert::AreEqual(Bool(false), numbers->getIsEmpty());

			// The same for empty one
			Assert::AreEqual(Bool(true), empty->getIsEmpty());
			Assert::AreEqual(Int(0), empty->getLength());
		}


		TEST_METHOD(Equals) {
			auto xs = makeList({ 1, 2, 3, 4, 5 });
			auto ys = makeList({ 1, 2, 3, 4, 6 });
			auto zs = makeList({ 1, 2, 3, 4, 5, 6 });
			auto ws = makeList({ 1, 2, 3, 4, 5 });
			Assert::IsTrue(xs == xs);
			Assert::IsFalse(xs == ys);
			Assert::IsFalse(xs == zs);
			Assert::IsTrue(xs == ws);
		}


		TEST_METHOD(Add) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5 });
			mutableList->add(Int(6));
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 6]", mutableList->toString()->getRaw().c_str());
		}


		TEST_METHOD(AddAll) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5 });
			mutableList->addAll(makePtr<ArrayList<Int>>({ 7, 8, 9 }));
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 7, 8, 9]", mutableList->toString()->getRaw().c_str());
		}


		TEST_METHOD(InsertAt) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5 });
			mutableList->insertAt(-3, Int(10));
			Assert::AreEqual(L"[1, 2, 10, 3, 4, 5]", mutableList->toString()->getRaw().c_str());

			// Out of range
			auto test = [mutableList]() {
				mutableList->insertAt(6, 137);
			};
			Assert::ExpectException<IndexError>(test);
		}


		TEST_METHOD(RemoveAt) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5 });
			mutableList->removeAt(-4);
			Assert::AreEqual(L"[1, 3, 4, 5]", mutableList->toString()->getRaw().c_str());

			// Out of range
			auto test = [mutableList]() {
				mutableList->removeAt(4);
			};
			Assert::ExpectException<IndexError>(test);
		}


		TEST_METHOD(Resize) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5, 7 });
			mutableList->resize(5);
			Assert::AreEqual(L"[1, 2, 3, 4, 5]", mutableList->toString()->getRaw().c_str());
			mutableList->resize(7, Int(6));
			Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 6]", mutableList->toString()->getRaw().c_str());

			// Must be non negative
			auto test = [mutableList]() {
				mutableList->resize(-1);
			};
			Assert::ExpectException<ValueError>(test);
		}


		TEST_METHOD(Set) {
			auto mutableList = makeList({ 1, 2, 3, 4, 6 });
			mutableList->set(-1, Int(5));
			Assert::AreEqual(L"[1, 2, 3, 4, 5]", mutableList->toString()->getRaw().c_str());

			// Out of range
			auto test = [mutableList]() {
				mutableList->set(5, 137);
			};
			Assert::ExpectException<IndexError>(test);
		}


		TEST_METHOD(Clear) {
			auto mutableList = makeList({ 1, 2, 3, 4, 5 });
			mutableList->clear();
			Assert::IsTrue(mutableList->getIsEmpty());
		}
	};
}