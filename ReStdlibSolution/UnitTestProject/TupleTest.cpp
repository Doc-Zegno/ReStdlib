#include "stdafx.h"
#include "CppUnitTest.h"

#include "Tuple.h"
#include "BasicString.h"
#include "Errors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
	TEST_CLASS(TupleTest) {
	public:
		TEST_METHOD(Tuple2Functionality) {
			auto tuple = makeTuple(-137, makeStr(L"Hello"));

			// Representation
			Assert::AreEqual(L"(-137, \"Hello\")", toString(tuple)->getRaw().c_str());

			// Accessors
			Assert::AreEqual(-137, tuple.getFirst());
			Assert::AreEqual(L"Hello", tuple.getSecond()->getRaw().c_str());

			// Equality
			Assert::IsTrue(tuple == makeTuple(-137, makeStr(L"Hello")));
			Assert::IsTrue(tuple != makeTuple(-138, makeStr(L"Hello")));
			Assert::IsTrue(tuple != makeTuple(-137, makeStr(L"Sample text")));
			Assert::IsTrue(tuple != makeTuple(-138, makeStr(L"Sample text")));

			// Comparable (operators)
			Assert::IsTrue(tuple < makeTuple(137, makeStr(L"Hello")));
			Assert::IsTrue(tuple < makeTuple(-137, makeStr(L"Zelda")));

			Assert::IsTrue(tuple > makeTuple(-138, makeStr(L"Hello")));
			Assert::IsTrue(tuple > makeTuple(-137, makeStr(L"Awesome")));

			Assert::IsTrue(tuple <= makeTuple(137, makeStr(L"Hello")));
			Assert::IsTrue(tuple <= makeTuple(-137, makeStr(L"Zelda")));
			Assert::IsTrue(tuple <= makeTuple(-137, makeStr(L"Hello")));

			Assert::IsTrue(tuple >= makeTuple(-138, makeStr(L"Hello")));
			Assert::IsTrue(tuple >= makeTuple(-137, makeStr(L"Awesome")));
			Assert::IsTrue(tuple >= makeTuple(-137, makeStr(L"Hello")));

			// Ñomparable (compareTo)
			Assert::AreEqual(1, compareTo(tuple, makeTuple(-138, makeStr(L"Hello"))));
			Assert::AreEqual(1, compareTo(tuple, makeTuple(-137, makeStr(L"Awesome"))));

			Assert::AreEqual(-1, compareTo(tuple, makeTuple(137, makeStr(L"Hello"))));
			Assert::AreEqual(-1, compareTo(tuple, makeTuple(-137, makeStr(L"Zelda"))));

			Assert::AreEqual(0, compareTo(tuple, makeTuple(-137, makeStr(L"Hello"))));
		}
	};
}
