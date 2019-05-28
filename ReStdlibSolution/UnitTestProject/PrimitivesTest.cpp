#include "stdafx.h"
#include "CppUnitTest.h"

#include "Primitives.h"
#include "BoxedPrimitives.h"
#include "BasicString.h"
#include "Errors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
	TEST_CLASS(PrimitivesTest) {
	public:
		TEST_METHOD(IntFunctionality) {
			// Representation
			Assert::AreEqual(L"-137", toString(-137)->getRaw().c_str());

			// Checked division
			Assert::AreEqual(3, divide(23, 7));
			auto test1 = []() {
				divide(5, 0);
			};
			Assert::ExpectException<ZeroDivisionError>(test1);

			// Checked modulo
			Assert::AreEqual(2, modulo(23, 7));
			auto test2 = []() {
				modulo(5, 0);
			};
			Assert::ExpectException<ZeroDivisionError>(test2);

			// Ñomparable
			Assert::AreEqual(1, compareTo(5, 4));
			Assert::AreEqual(-1, compareTo(4, 5));
			Assert::AreEqual(0, compareTo(5, 5));
		}


		TEST_METHOD(BoxedIntFunctionality) {
			auto number = 137;
			auto boxed = box(number);
			
			// Boxing
			Assert::AreEqual(number, boxed->unbox());

			// Representation
			Assert::AreEqual(L"-137", box(-137)->toString()->getRaw().c_str());

			// Comparable (operators)
			Assert::IsTrue(box(5) == box(5));
			Assert::IsFalse(box(5) != box(5));
			Assert::IsTrue(box(5) > box(4));
			Assert::IsTrue(box(5) >= box(5));
			Assert::IsTrue(box(5) < box(6));
			Assert::IsTrue(box(5) <= box(6));

			// Comparable (compareTo)
			Assert::AreEqual(1, compareTo(5, 4));
			Assert::AreEqual(-1, compareTo(4, 5));
			Assert::AreEqual(0, compareTo(5, 5));

			// Arithmetic
			Assert::IsTrue(box(5) == box(2) + box(3));
			Assert::IsTrue(box(5) == box(8) - box(3));
			Assert::IsTrue(box(10) == box(5) * box(2));
			Assert::IsTrue(box(5) == box(125) / box(25));
			Assert::IsTrue(box(5) == box(12) % box(7));
			
			// Checked arithmetic
			Assert::IsTrue(box(5) == divide(box(125), box(25)));
			auto test1 = []() {
				divide(box(5), box(0));
			};
			Assert::ExpectException<ZeroDivisionError>(test1);
			Assert::IsTrue(box(5) == modulo(box(12), box(7)));
			auto test2 = []() {
				modulo(box(5), box(0));
			};
			Assert::ExpectException<ZeroDivisionError>(test2);
		}
	};
}