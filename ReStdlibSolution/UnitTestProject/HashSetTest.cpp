#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "HashSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
    TEST_CLASS(HashSetTest) {
	private:
		Ptr<Set<Int>> empty = makeSet<Int>();
		Ptr<Set<Int>> set = makeSet({ 1, 2, 2, 3, 4, 3, 1, 5 });

    public:
		TEST_METHOD(ToString) {
			Assert::AreEqual(L"{}", empty->toString()->getRaw().c_str());
		}


		TEST_METHOD(Length) {
			// For empty
			Assert::IsTrue(empty->getIsEmpty());
			Assert::IsTrue(empty->getHasLength());
			Assert::AreEqual(0, empty->getLength());

			// For non empty
			Assert::IsFalse(set->getIsEmpty());
			Assert::IsTrue(set->getHasLength());
			Assert::AreEqual(5, set->getLength());
		}


		TEST_METHOD(Contains) {
			for (auto i = 1; i <= 5; i++) {
				Assert::IsTrue(set->contains(i));
				Assert::IsFalse(empty->contains(i));
			}
			Assert::IsFalse(set->contains(6));
		}


		TEST_METHOD(Equals) {
			auto copy1 = makeSet({ 1, 2, 3, 4, 5 });
			auto copy2 = makeSet<Int>(set);
			Assert::IsTrue(set == copy1);
			Assert::IsTrue(set == copy2);
			Assert::IsFalse(set == empty);
			Assert::IsFalse(set == makeSet({ 1, 2, 3, 4, 7 }));
		}


		TEST_METHOD(UnionIntersectionDifference) {
			auto other = makeSet({ 1, 3, 5, 7, 9 });
			Assert::IsTrue(set->unioned(other) == makeSet({ 1, 2, 3, 4, 5, 7, 9 }));
			Assert::IsTrue(set->intersection(other) == makeSet({ 1, 3, 5 }));
			Assert::IsTrue(set->difference(other) == makeSet({ 2, 4 }));
		}


		TEST_METHOD(Add) {
			auto mutableSet = makeSet({ 1, 2, 2, 3, 4, 3, 1, 5 });
			mutableSet->add(Int(6));
			Assert::IsTrue(mutableSet == makeSet({ 1, 2, 3, 4, 5, 6 }));
		}


		TEST_METHOD(AddAll) {
			auto mutableSet = makeSet({ 1, 2, 2, 3, 4, 3, 1, 5 });
			mutableSet->addAll(makeSet({ 7, 8, 9 }));
			Assert::IsTrue(mutableSet == makeSet({ 1, 2, 3, 4, 5, 7, 8, 9 }));
		}


		TEST_METHOD(Remove) {
			auto mutableSet = makeSet({ 1, 2, 2, 3, 4, 3, 1, 5 });
			mutableSet->remove(1);
			Assert::IsTrue(mutableSet == makeSet({ 2, 3, 4, 5 }));

			auto mutableEmpty = makeSet<Int>();
			mutableEmpty->remove(1);
			Assert::IsTrue(mutableEmpty->getIsEmpty());
		}


		TEST_METHOD(RemoveAll) {
			auto mutableSet = makeSet({ 1, 2, 2, 3, 4, 3, 1, 5 });
			mutableSet->removeAll(makeSet({ 3, 5, 7, 9 }));
			Assert::IsTrue(mutableSet == makeSet({ 1, 2, 4 }));
		}


		TEST_METHOD(Clear) {
			auto mutableSet = makeSet({ 1, 2, 2, 3, 4, 3, 1, 5 });
			mutableSet->clear();
			Assert::IsTrue(mutableSet->getIsEmpty());
			Assert::AreEqual(Int(0), mutableSet->getLength());
			Assert::AreEqual(L"{}", mutableSet->toString()->getRaw().c_str());
		}
    };
}