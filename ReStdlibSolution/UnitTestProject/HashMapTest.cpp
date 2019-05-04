#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "HashMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
	TEST_CLASS(HashMapTest) {
	public:
		TEST_METHOD(BasicFunctionality) {
			// For empty
			auto empty = makeMap<Int, Bool>();
			Assert::AreEqual(L"{}", empty->toString()->getRaw().c_str());
			Assert::AreEqual(Int(0), empty->getLength());
			Assert::IsTrue(empty->getHasLength());
			Assert::IsTrue(empty->getIsEmpty());

			// For not empty
			auto map = makeMap<Int, Bool>({ Tuple<Int, Bool>(0, true), Tuple<Int, Bool>(1, false), Tuple<Int, Bool>(2, true) });
			Assert::IsFalse(map->getIsEmpty());
			Assert::AreEqual(Int(3), map->getLength());

			// Contains
			Assert::IsTrue(map->containsKey(0));
			Assert::IsFalse(map->containsKey(-1));

			// Get
			Assert::AreEqual(Bool(true), map->get(Int(0)));
			Assert::AreEqual(Bool(false), map->get(Int(1)));
			Assert::AreEqual(Bool(true), map->get(Int(2)));

			// GetKeys
			auto keys = map->getKeys();
			Assert::IsTrue((*keys) == makeSet<Int>({ 0, 1, 2 }));

			// GetValues
			auto values = map->getValues();
			auto valuesSet = makeSet<Bool>(values);
			Assert::IsTrue((*valuesSet) == makeSet<Bool>({ true, false }));
		}


		TEST_METHOD(MutatingFunctionality) {
			auto map = makeMap<Int, Bool>({ Tuple<Int, Bool>(0, true), Tuple<Int, Bool>(1, false), Tuple<Int, Bool>(2, true) });

			// Set
			map->set(0, false);
			Assert::AreEqual(Bool(false), map->get(0));
			map->set(3, true);
			Assert::AreEqual(Bool(true), map->get(3));
			Assert::AreEqual(Int(4), map->getLength());

			// Remove
			map->remove(3);
			Assert::IsFalse(map->containsKey(3));
			map->remove(3);  // Shouldn't throw

			// Clear
			map->clear();
			Assert::IsTrue(map->getIsEmpty());
			Assert::AreEqual(Int(0), map->getLength());
		}
	};
}