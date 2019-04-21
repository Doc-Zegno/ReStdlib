#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
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


    public:
        TEST_METHOD(BasicFunctionality) {
            auto numbers = Ptr<List<Int>>(new ArrayList<Int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
            auto strings = Ptr<List<Ptr<String>>>(
                new ArrayList<Ptr<String>>(
                    {
                        Ptr<String>(new String(L"Hello, World!")),
                        Ptr<String>(),
                        Ptr<String>(new String(L"Sample Text")),
                        Ptr<String>(new String(L"Serious Arguments"))
                    }));

            // Indices
            auto indices = numbers->getIndices();
            Assert::AreEqual(Bool(true), indices->getHasLength());
            Assert::AreEqual(Int(10), indices->getLength());
            Assert::AreEqual(Bool(false), indices->getIsEmpty());
            Assert::AreEqual(L"[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]", makePtr<ArrayList<Int>>(indices)->toString()->getRaw().c_str());

            // Enumerating
            auto enumerate = strings->enumerate();
            Assert::AreEqual(Bool(true), enumerate->getHasLength());
            Assert::AreEqual(Int(4), enumerate->getLength());
            Assert::AreEqual(Bool(false), enumerate->getIsEmpty());
            Assert::AreEqual(L"(0, Hello, World!)::(1, null)::(2, Sample Text)::(3, Serious Arguments)::[]", enumerate->toString()->getRaw().c_str());

            // Zipping
            auto zipped = zip(strings, numbers);
            Assert::AreEqual(Bool(true), zipped->getHasLength());
            Assert::AreEqual(Int(4), zipped->getLength());
            Assert::AreEqual(Bool(false), zipped->getIsEmpty());
            Assert::AreEqual(L"(Hello, World!, 1)::(null, 2)::(Sample Text, 3)::(Serious Arguments, 4)::[]", zipped->toString()->getRaw().c_str());

            // Mapping
            auto mapping = Ptr<Function<Int, Int>>(new SquareFunction());
            auto mapped = numbers->map(mapping);
            Assert::AreEqual(Bool(true), mapped->getHasLength());
            Assert::AreEqual(Int(10), mapped->getLength());
            Assert::AreEqual(Bool(false), mapped->getIsEmpty());
            Assert::AreEqual(L"1::4::9::16::25::36::49::64::81::100::[]", mapped->toString()->getRaw().c_str());
        }

    };
}