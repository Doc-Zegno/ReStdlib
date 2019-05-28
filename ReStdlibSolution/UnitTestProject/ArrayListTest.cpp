#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "ArrayList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {		
	TEST_CLASS(ArrayListTest) {
	public:
		TEST_METHOD(BasicFunctionality) {
            auto empty = makePtr<ArrayList<Int>>(Int(0), Int(0));
            auto repeating = makePtr<ArrayList<Int>>(Int(5), Int(2));
            auto copy = makePtr<ArrayList<Int>>(repeating);
            auto numbers = Ptr<List<Int>>(new ArrayList<Int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));

            // Representation test
            Assert::AreEqual(L"[]", empty->toString()->getRaw().c_str());
            Assert::AreEqual(L"[2, 2, 2, 2, 2]", repeating->toString()->getRaw().c_str());
            Assert::AreEqual(L"[2, 2, 2, 2, 2]", copy->toString()->getRaw().c_str());
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", numbers->toString()->getRaw().c_str());

            // Get rest
            Assert::AreEqual(L"[2, 3, 4, 5, 6, 7, 8, 9, 10]", numbers->getRest()->toString()->getRaw().c_str());

            // Get first and last
            Assert::AreEqual(Int(1), numbers->getFirst());
            Assert::AreEqual(Int(10), numbers->getLast());

            // Get
            Assert::AreEqual(Int(3), numbers->get(2));
            Assert::AreEqual(Int(7), numbers->get(-4));

            // Skip and take
            Assert::AreEqual(L"[1, 2, 3, 4]", numbers->take(4)->toString()->getRaw().c_str());
            Assert::AreEqual(L"[5, 6, 7, 8, 9, 10]", numbers->skip(4)->toString()->getRaw().c_str());

            // Skip and take (too much)
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", numbers->take(100)->toString()->getRaw().c_str());
            Assert::AreEqual(L"[]", numbers->skip(100)->toString()->getRaw().c_str());

            // Skip and take (too few)
            Assert::AreEqual(L"[]", numbers->take(0)->toString()->getRaw().c_str());
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", numbers->skip(0)->toString()->getRaw().c_str());

            // Slice
            Assert::AreEqual(L"[2, 4, 6, 8]", numbers->getSlice(1, -1, 2)->toString()->getRaw().c_str());
            Assert::AreEqual(L"[]", numbers->getSlice(10, 10, 1)->toString()->getRaw().c_str());

            // Length and emptyness
            Assert::AreEqual(Bool(true), numbers->getHasLength());
            Assert::AreEqual(Int(10), numbers->getLength());
            Assert::AreEqual(Bool(false), numbers->getIsEmpty());

            // The same for empty one
            Assert::AreEqual(Bool(true), empty->getIsEmpty());
            Assert::AreEqual(Int(0), empty->getLength());

            // Equality tests
            auto xs = makePtr<ArrayList<Int>>({ 1, 2, 3, 4, 5 });
            auto ys = makePtr<ArrayList<Int>>({ 1, 2, 3, 4, 6 });
            auto zs = makePtr<ArrayList<Int>>({ 1, 2, 3, 4, 5, 6 });
            auto ws = makePtr<ArrayList<Int>>({ 1, 2, 3, 4, 5 });
            Assert::IsTrue(xs == xs);
            Assert::IsFalse(xs == ys);
            Assert::IsFalse(xs == zs);
            Assert::IsTrue(xs == ws);
		}


        TEST_METHOD(MutatingFunctionality) {
            auto numbers = makePtr<ArrayList<Int>>({ 1, 2, 3, 4, 5 });
            
            // Add
            numbers->add(Int(6));
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6]", numbers->toString()->getRaw().c_str());

            // AddAll
            numbers->addAll(makePtr<ArrayList<Int>>({ 7, 8, 9 }));
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9]", numbers->toString()->getRaw().c_str());

            // InsertAt
            numbers->insertAt(-3, Int(10));
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 10, 7, 8, 9]", numbers->toString()->getRaw().c_str());

            // RemoveAt
            numbers->removeAt(-4);
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9]", numbers->toString()->getRaw().c_str());

            // Resize
            numbers->resize(5);
            Assert::AreEqual(L"[1, 2, 3, 4, 5]", numbers->toString()->getRaw().c_str());
            numbers->resize(7, Int(6));
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 6]", numbers->toString()->getRaw().c_str());

            // Set
            numbers->set(-1, Int(7));
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7]", numbers->toString()->getRaw().c_str());

            // Clear
            numbers->clear();
            Assert::IsTrue(numbers->getIsEmpty());
        }


        TEST_METHOD(SliceBasicFunctionality) {
            auto numbers = Ptr<List<Int>>(new ArrayList<Int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
            auto evens = numbers->getSlice(1, 10, 2);
            auto odds = numbers->getSlice(0, 10, 2);
            auto empty = numbers->getSlice(10, 10, 1);
            auto one = numbers->getSlice(0, 1, 1);

            // Representation test
            Assert::AreEqual(L"[]", empty->toString()->getRaw().c_str());
            Assert::AreEqual(L"[1]", one->toString()->getRaw().c_str());
            Assert::AreEqual(L"[2, 4, 6, 8, 10]", evens->toString()->getRaw().c_str());
            Assert::AreEqual(L"[1, 3, 5, 7, 9]", odds->toString()->getRaw().c_str());

            // Get rest
            Assert::AreEqual(L"[3, 5, 7, 9]", odds->getRest()->toString()->getRaw().c_str());

            // Get first and last
            Assert::AreEqual(Int(2), evens->getFirst());
            Assert::AreEqual(Int(10), evens->getLast());

            // Get
            Assert::AreEqual(Int(5), odds->get(2));
            Assert::AreEqual(Int(3), odds->get(-4));

            // Skip and take
            Assert::AreEqual(L"[2, 4, 6, 8]", evens->take(4)->toString()->getRaw().c_str());
            Assert::AreEqual(L"[10]", evens->skip(4)->toString()->getRaw().c_str());

            // Skip and take (too much)
            Assert::AreEqual(L"[1, 3, 5, 7, 9]", odds->take(100)->toString()->getRaw().c_str());
            Assert::AreEqual(L"[]", odds->skip(100)->toString()->getRaw().c_str());

            // Skip and take (too few)
            Assert::AreEqual(L"[]", evens->take(0)->toString()->getRaw().c_str());
            Assert::AreEqual(L"[2, 4, 6, 8, 10]", evens->skip(0)->toString()->getRaw().c_str());

            // Slice
            Assert::AreEqual(L"[4, 8]", evens->getSlice(1, -1, 2)->toString()->getRaw().c_str());
            Assert::AreEqual(L"[]", odds->getSlice(5, 5, 1)->toString()->getRaw().c_str());

            // Length and emptyness
            Assert::AreEqual(Bool(true), evens->getHasLength());
            Assert::AreEqual(Int(5), evens->getLength());
            Assert::AreEqual(Bool(false), evens->getIsEmpty());

            // The same for empty one
            Assert::AreEqual(Bool(true), empty->getIsEmpty());
            Assert::AreEqual(Int(0), empty->getLength());
        }


        TEST_METHOD(SliceMutatingFunctionality) {
            auto numbers = Ptr<MutableList<Int>>(new ArrayList<Int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
            auto evens = numbers->getMutableSlice(1, 10, 2);
            evens->set(0, Int(-2));
            Assert::AreEqual(L"[-2, 4, 6, 8, 10]", evens->toString()->getRaw().c_str());
        }

	};
}