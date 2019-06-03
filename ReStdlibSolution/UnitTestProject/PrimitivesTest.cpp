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
	private:
		Bool almostEqual(Float x, Float y) {
			return std::abs(x - y) < 1.0e-10;
		}

		Bool almostEqual(Ptr<BoxedFloat> x, Ptr<BoxedFloat> y) {
			return almostEqual(x->unbox(), y->unbox());
		}


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

			// Float division
			Assert::IsTrue(almostEqual(5.0, fdivide(125, 25)));

			// Ñomparable
			Assert::AreEqual(1, compareTo(5, 4));
			Assert::AreEqual(-1, compareTo(4, 5));
			Assert::AreEqual(0, compareTo(5, 5));
		}


		TEST_METHOD(FloatFunctionality) {
			// Representation
			//Assert::AreEqual(L"-137.42", toString(-137.42)->getRaw().c_str());

			// Comparable
			Assert::AreEqual(1, compareTo(5.0, 4.0));
			Assert::AreEqual(-1, compareTo(4.0, 5.0));
		}


		TEST_METHOD(CharFunctionality) {
			// Representation
			Assert::AreEqual(L"A", toString(L'A')->getRaw().c_str());
			Assert::AreEqual(L"'\\n'", toString(L'\n', true)->getRaw().c_str());

			// Comparable
			Assert::AreEqual(1, compareTo(L'B', L'A'));
			Assert::AreEqual(-1, compareTo(L'A', L'B'));
			Assert::AreEqual(0, compareTo(L'A', L'A'));
		}


		TEST_METHOD(BoolFunctionality) {
			// Representation
			Assert::AreEqual(L"true", toString(true)->getRaw().c_str());
			Assert::AreEqual(L"false", toString(false)->getRaw().c_str());
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
			Assert::AreEqual(1, compareTo(box(5), box(4)));
			Assert::AreEqual(-1, compareTo(box(4), box(5)));
			Assert::AreEqual(0, compareTo(box(5), box(5)));

			// Arithmetic
			Assert::IsTrue(box(5) == box(2) + box(3));
			Assert::IsTrue(box(5) == box(8) - box(3));
			Assert::IsTrue(box(10) == box(5) * box(2));
			Assert::IsTrue(box(5) == box(125) / box(25));
			Assert::IsTrue(box(5) == box(12) % box(7));

			// Float division
			Assert::IsTrue(almostEqual(box(5.0), fdivide(box(125), box(25))));
			
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


		TEST_METHOD(BoxedFloatFunctionality) {
			auto number = 137.42;
			auto boxed = box(number);

			// Boxing
			Assert::IsTrue(almostEqual(number, boxed->unbox()));

			// Representation
			//Assert::AreEqual(L"137.42", boxed->toString()->getRaw().c_str());

			// Comparable (operators)
			Assert::IsTrue(box(5.0) > box(4.0));
			Assert::IsFalse(box(5.0) < box(4.0));
			Assert::IsTrue(box(5.0) >= box(4.0));
			Assert::IsFalse(box(5.0) <= box(4.0));

			// Comparable (compareTo)
			Assert::AreEqual(1, compareTo(box(5.0), box(4.0)));
			Assert::AreEqual(-1, compareTo(box(4.0), box(5.0)));

			// Arithmetic
			Assert::IsTrue(almostEqual(box(5.0), box(2.0) + box(3.0)));
			Assert::IsTrue(almostEqual(box(5.0), box(8.0) - box(3.0)));
			Assert::IsTrue(almostEqual(box(10.0), box(5.0) * box(2.0)));
			Assert::IsTrue(almostEqual(box(5.0), box(125.0) / box(25.0)));
		}


		TEST_METHOD(BoxedCharFunctionality) {
			// Boxing
			Assert::AreEqual(L'A', box(L'A')->unbox());

			// Representation
			Assert::AreEqual(L"A", toString(box(L'A'))->getRaw().c_str());
			Assert::AreEqual(L"'\\n'", toString(box(L'\n'), true)->getRaw().c_str());

			// Comparable (operators)
			Assert::IsTrue(box(L'B') > box(L'A'));
			Assert::IsFalse(box(L'B') < box(L'A'));
			Assert::IsTrue(box(L'B') >= box(L'A'));
			Assert::IsFalse(box(L'B') <= box(L'A'));
			Assert::IsTrue(box(L'A') == box(L'A'));
			Assert::IsFalse(box(L'A') != box(L'A'));

			// Comparable (compareTo)
			Assert::AreEqual(1, compareTo(box(L'B'), box(L'A')));
			Assert::AreEqual(-1, compareTo(box(L'A'), box(L'B')));
			Assert::AreEqual(0, compareTo(box(L'A'), box(L'A')));
		}


		TEST_METHOD(BoxedBoolFunctionality) {
			// Boxing
			Assert::AreEqual(true, box(true)->unbox());
			Assert::AreEqual(false, box(false)->unbox());

			// Representation
			Assert::AreEqual(L"true", box(true)->toString()->getRaw().c_str());
			Assert::AreEqual(L"false", box(false)->toString()->getRaw().c_str());
		}
	};
}