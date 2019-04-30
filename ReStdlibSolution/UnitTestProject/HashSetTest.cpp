#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "HashSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
    TEST_CLASS(HashSetTest) {
    public:
        TEST_METHOD(BasicFunctionality) {
            // Common test for empty
            auto empty = makeSet<Int>();
            Assert::IsTrue(empty->getIsEmpty());
            Assert::IsTrue(empty->getHasLength());
            Assert::AreEqual(Int(0), empty->getLength());
            Assert::AreEqual(L"{}", empty->toString()->getRaw().c_str());

            // Common test for non-empty
            auto set = makeSet<Int>({ 1, 2, 2, 3, 4, 3, 1, 5 });
            Assert::IsFalse(set->getIsEmpty());
            Assert::IsTrue(set->getHasLength());
            Assert::AreEqual(Int(5), set->getLength());
            for (auto i = 1; i <= 5; i++) {
                Assert::IsTrue(set->contains(Int(i)));
            }
            Assert::IsFalse(set->contains(Int(6)));
            
            // Equality
            auto copy1 = makeSet<Int>({ 1, 2, 3, 4, 5 });
            auto copy2 = makeSet<Int>(set);
            Assert::IsTrue((*set) == copy1);
            Assert::IsTrue((*set) == copy2);
            Assert::IsFalse((*set) == empty);
            Assert::IsFalse((*set) == makeSet<Int>({ 1, 2, 3, 4, 7 }));

            // Union/intersection/difference
            auto other = makeSet<Int>({ 1, 3, 5, 7, 9 });
            Assert::IsTrue(*(set->unioned(other)) == makeSet<Int>({ 1, 2, 3, 4, 5, 7, 9 }));
            Assert::IsTrue(*(set->intersection(other)) == makeSet<Int>({ 1, 3, 5 }));
            Assert::IsTrue(*(set->difference(other)) == makeSet<Int>({ 2, 4 }));
        }


        TEST_METHOD(MutatingFunctionality) {
            auto set = makeSet<Int>({ 1, 2, 2, 3, 4, 3, 1, 5 });

            // Add
            set->add(Int(6));
            Assert::IsTrue((*set) == makeSet<Int>({ 1, 2, 3, 4, 5, 6 }));

            // AddAll
            set->addAll(makeSet<Int>({ 7, 8, 9 }));
            Assert::IsTrue((*set) == makeSet<Int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

            // Remove
            set->remove(Int(1));
            Assert::IsTrue((*set) == makeSet<Int>({ 2, 3, 4, 5, 6, 7, 8, 9 }));

            // RemoveAll
            set->removeAll(makeSet<Int>({ 3, 5, 7, 9 }));
            Assert::IsTrue((*set) == makeSet<Int>({ 2, 4, 6, 8 }));

            // Clear
            set->clear();
            Assert::IsTrue(set->getIsEmpty());
            Assert::AreEqual(Int(0), set->getLength());
            Assert::AreEqual(L"{}", set->toString()->getRaw().c_str());
        }
    };
}