#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "HashMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
	TEST_CLASS(HashMapTest) {
	private:
		Ptr<Map<Int, Bool>> map = makeMap<Int, Bool>({ Tuple<Int, Bool>(0, true), Tuple<Int, Bool>(1, false), Tuple<Int, Bool>(2, true) });
		Ptr<Map<Int, Bool>> empty = makeMap<Int, Bool>();

	public:
		TEST_METHOD(ToString) {
			Assert::AreEqual(L"{}", empty->toString()->getRaw().c_str());
		}


		TEST_METHOD(Length) {
			// For empty
			Assert::AreEqual(Int(0), empty->getLength());
			Assert::IsTrue(empty->getHasLength());
			Assert::IsTrue(empty->getIsEmpty());

			// For not empty
			Assert::IsFalse(map->getIsEmpty());
			Assert::AreEqual(Int(3), map->getLength());
		}


		TEST_METHOD(Contains) {
			Assert::IsTrue(map->containsKey(0));
			Assert::IsFalse(map->containsKey(-1));
		}


		TEST_METHOD(Get) {
			Assert::AreEqual(Bool(true), map->get(0));
			Assert::AreEqual(Bool(false), map->get(1));
			Assert::AreEqual(Bool(true), map->get(2));

			// No such key
			auto test = [this]() {
				map->get(-1);
			};
			Assert::ExpectException<KeyError>(test);
		}


		TEST_METHOD(GetKeys) {
			auto keys = map->getKeys();
			Assert::IsTrue(keys == makeSet<Int>({ 0, 1, 2 }));
		}


		TEST_METHOD(GetValues) {
			auto values = map->getValues();
			auto valuesSet = makeSet<Bool>(values);
			Assert::IsTrue(valuesSet == makeSet<Bool>({ true, false }));
		}


		TEST_METHOD(Set) {
			auto mutableMap = makeMap<Int, Bool>({ Tuple<Int, Bool>(0, true), Tuple<Int, Bool>(1, false), Tuple<Int, Bool>(2, true) });
			mutableMap->set(0, false);
			Assert::AreEqual(Bool(false), mutableMap->get(0));
			mutableMap->set(3, true);
			Assert::AreEqual(Bool(true), mutableMap->get(3));
			Assert::AreEqual(Int(4), mutableMap->getLength());
		}


		TEST_METHOD(Remove) {
			auto mutableMap = makeMap<Int, Bool>({ Tuple<Int, Bool>(0, true), Tuple<Int, Bool>(1, false), Tuple<Int, Bool>(2, true) });
			mutableMap->remove(3);
			Assert::IsFalse(mutableMap->containsKey(3));
			mutableMap->remove(3);  // Shouldn't throw
		}


		TEST_METHOD(Clear) {
			auto mutableMap = makeMap<Int, Bool>({ Tuple<Int, Bool>(0, true), Tuple<Int, Bool>(1, false), Tuple<Int, Bool>(2, true) });
			mutableMap->clear();
			Assert::IsTrue(mutableMap->getIsEmpty());
			Assert::AreEqual(Int(0), mutableMap->getLength());
		}
	};
}