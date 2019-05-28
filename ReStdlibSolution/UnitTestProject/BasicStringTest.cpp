#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
	TEST_CLASS(BasicStringTest) {
	public:
		TEST_METHOD(BasicFunctionality) {
			auto string = makeStr(L"Sample text");
			
			// Representation
			Assert::AreEqual(L"Sample text", string->toString()->getRaw().c_str());
			Assert::AreEqual(L"Sample text", string->getRaw().c_str());

			// Indexing
			Assert::AreEqual(L'S', string->get(0));
			Assert::AreEqual(L'S', string[0]);
			Assert::AreEqual(L'x', string->get(-2));
			Assert::AreEqual(L'x', string[-2]);

			// Take/skip
			Assert::AreEqual(L"ple text", string->skip(3)->toString()->getRaw().c_str());
			Assert::AreEqual(L"Sam", string->take(3)->toString()->getRaw().c_str());

			// first/last
			Assert::AreEqual(L'S', string->getFirst());
			Assert::AreEqual(L't', string->getLast());

			// Other stuff
			Assert::AreEqual(L"ample text", string->getRest()->toString()->getRaw().c_str());
			Assert::IsFalse(string->getIsEmpty());
			Assert::IsTrue(string->getHasLength());
			Assert::AreEqual(11, string->getLength());
		}


		TEST_METHOD(ComparableFunctionality) {
			auto string = makeStr(L"Sample text");
			Assert::IsTrue(string == string);
			Assert::IsTrue(string == makeStr(L"Sample text"));
			Assert::IsTrue(string != makeStr(L"Sample texz"));

			Assert::IsFalse(string > makeStr(L"Sample text"));
			Assert::IsTrue(string >= makeStr(L"Sample text"));
			Assert::IsTrue(string <= makeStr(L"Sample text"));
			Assert::IsTrue(string > makeStr(L"Hello, world!"));
			Assert::IsTrue(string < makeStr(L"Serious arguments"));
		}


		TEST_METHOD(SliceBasicFunctionality) {
			auto string = makeStr(L"Sample text");
			auto slice = string->getSlice(1, -2, 3);
			Assert::AreEqual(L"alt", slice->toString()->getRaw().c_str());
		}
	};
}