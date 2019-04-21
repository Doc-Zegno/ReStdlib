#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "ArrayList.h"
#include "Range.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
    TEST_CLASS(RangeTest) {
    public:
        TEST_METHOD(BasicFunctionality) {
            auto empty = makePtr<Range>(0, 0, 1);
            auto numbers = makePtr<Range>(1, 11, 1);

            // Representation test
            Assert::AreEqual(L"[]", makePtr<ArrayList<Int>>(empty)->toString()->getRaw().c_str());
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers)->toString()->getRaw().c_str());

            // Get rest
            Assert::AreEqual(L"[2, 3, 4, 5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers->getRest())->toString()->getRaw().c_str());

            // Get first and last
            Assert::AreEqual(Int(1), numbers->getFirst());
            Assert::AreEqual(Int(10), numbers->getLast());

            // Get
            Assert::AreEqual(Int(3), numbers->get(2));
            Assert::AreEqual(Int(7), numbers->get(-4));

            // Skip and take
            Assert::AreEqual(L"[1, 2, 3, 4]", makePtr<ArrayList<Int>>(numbers->take(4))->toString()->getRaw().c_str());
            Assert::AreEqual(L"[5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers->skip(4))->toString()->getRaw().c_str());

            // Skip and take (too much)
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers->take(100))->toString()->getRaw().c_str());
            Assert::AreEqual(L"[]", makePtr<ArrayList<Int>>(numbers->skip(100))->toString()->getRaw().c_str());

            // Skip and take (too few)
            Assert::AreEqual(L"[]", makePtr<ArrayList<Int>>(numbers->take(0))->toString()->getRaw().c_str());
            Assert::AreEqual(L"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]", makePtr<ArrayList<Int>>(numbers->skip(0))->toString()->getRaw().c_str());

            // Slice
            Assert::AreEqual(L"[2, 4, 6, 8]", makePtr<ArrayList<Int>>(numbers->getSlice(1, -1, 2))->toString()->getRaw().c_str());
            Assert::AreEqual(L"[]", makePtr<ArrayList<Int>>(numbers->getSlice(10, 10, 1))->toString()->getRaw().c_str());

            // Length and emptyness
            Assert::AreEqual(Bool(true), numbers->getHasLength());
            Assert::AreEqual(Int(10), numbers->getLength());
            Assert::AreEqual(Bool(false), numbers->getIsEmpty());

            // The same for empty one
            Assert::AreEqual(Bool(true), empty->getIsEmpty());
            Assert::AreEqual(Int(0), empty->getLength());
        }

    };
}