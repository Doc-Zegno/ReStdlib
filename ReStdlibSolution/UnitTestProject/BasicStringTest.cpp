#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
	TEST_CLASS(BasicStringTest) {
	private:
		Ptr<String> string = makeStr(L"Sample text");
		Ptr<String> empty = makeStr(L"");

	public:
		TEST_METHOD(ToString) {
			Assert::AreEqual(L"Sample text", string->toString()->getRaw().c_str());
			Assert::AreEqual(L"Sample text", string->getRaw().c_str());
		}


		TEST_METHOD(GetAndIndexing) {
			Assert::AreEqual(L'S', string->get(0));
			Assert::AreEqual(L'S', string[0]);
			Assert::AreEqual(L'x', string->get(-2));
			Assert::AreEqual(L'x', string[-2]);
		}


		TEST_METHOD(TakeAndSkip) {
			Assert::AreEqual(L"ple text", string->skip(3)->toString()->getRaw().c_str());
			Assert::AreEqual(L"Sam", string->take(3)->toString()->getRaw().c_str());

			// Skip and take (too much)
			Assert::AreEqual(L"Sample text", string->take(100)->toString()->getRaw().c_str());
			Assert::AreEqual(L"", string->skip(100)->toString()->getRaw().c_str());

			// Skip and take (too few)
			Assert::AreEqual(L"", string->take(0)->toString()->getRaw().c_str());
			Assert::AreEqual(L"Sample text", string->skip(0)->toString()->getRaw().c_str());
		}


		TEST_METHOD(GetFirst) {
			Assert::AreEqual(L'S', string->getFirst());

			// Empty must throw
			auto test = [this]() {
				empty->getFirst();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(GetLast) {
			Assert::AreEqual(L't', string->getLast());

			// Empty must throw
			auto test = [this]() {
				empty->getLast();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(GetRest) {
			Assert::AreEqual(L"ample text", string->getRest()->toString()->getRaw().c_str());

			// Empty must throw
			auto test = [this]() {
				empty->getRest();
			};
			Assert::ExpectException<EmptyIterableError>(test);
		}


		TEST_METHOD(LengthAndEmptyness) {
			Assert::IsFalse(string->getIsEmpty());
			Assert::IsTrue(string->getHasLength());
			Assert::AreEqual(11, string->getLength());

			// The same for empty
			Assert::IsTrue(empty->getIsEmpty());
			Assert::AreEqual(0, empty->getLength());
		}


		TEST_METHOD(Contains) {
			Assert::IsTrue(string->contains(makeStr(L"Sample")));
			Assert::IsTrue(string->contains(makeStr(L"text")));
			Assert::IsTrue(string->contains(makeStr(L"ple te")));
			Assert::IsTrue(string->contains(makeStr(L"a")));

			Assert::IsFalse(string->contains(makeStr(L"Hello")));
			Assert::IsFalse(string->contains(makeStr(L"b")));

			Assert::IsFalse(empty->contains(makeStr(L"world")));
			Assert::IsFalse(empty->contains(makeStr(L"z")));
		}


		TEST_METHOD(ComparableFunctionality) {
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
			auto slice = string->getSlice(1, -2, 3);
			Assert::AreEqual(L"alt", slice->toString()->getRaw().c_str());
		}
	};
}