#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "ArrayList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
    TEST_CLASS(IterableTest) {
    public:
        TEST_METHOD(BasicFunctionality) {
            auto numbers = Ptr<List<Int>>(new ArrayList<Int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));

            // Indices
            Assert::AreEqual(L"[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]", makePtr<ArrayList<Int>>(numbers->getIndices())->toString()->getRaw().c_str());
        }

    };
}