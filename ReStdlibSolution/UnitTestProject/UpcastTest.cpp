#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "ArrayList.h"
#include "BoxedPrimitives.h"
#include "Upcast.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
	static Int cube(Int value) {
		return value * value * value;
	}


	static Ptr<String> getRepresentation(Ptr<Any> value) {
		return value->toString();
	}


	TEST_CLASS(UpcastTest) {
	private:
		Ptr<List<Int>> numbers = makeList({ 1, 2, 3, 4, 5 });
		Ptr<ArrayList<Ptr<ArrayList<Int>>>> matrix = makeList({ makeList({ 1, 2, 3 }), makeList({ 4, 5, 6 }) });

	public:
		TEST_METHOD(BoxingIterableUpcast) {
			auto iterable = Ptr<Iterable<Int>>(numbers);
			auto boxed = upcastPtr<Iterable<Ptr<Any>>>(numbers);
			Assert::AreEqual(L"1::2::3::4::5::[]", boxed->toString()->getRaw().c_str());
		}


		TEST_METHOD(CovariantIterableUpcast) {
			auto covariant = upcastPtr<Iterable<Ptr<Any>>>(numbers);
			Assert::AreEqual(L"1::2::3::4::5::[]", covariant->toString()->getRaw().c_str());
		}


		TEST_METHOD(NestedCovariantIterableUpcast) {
			auto covariant = upcastPtr<Iterable<Ptr<Iterable<Ptr<Any>>>>>(matrix);
			Assert::AreEqual(L"1::2::3::[]::4::5::6::[]::[]", covariant->toString()->getRaw().c_str());
		}


		TEST_METHOD(BoxingFunctionUpcast) {
			auto cubed = numbers->map(upcast<Ptr<Function<Int, Int>>>(cube));
			Assert::AreEqual(L"1::8::27::64::125::[]", cubed->toString()->getRaw().c_str());
		}


		TEST_METHOD(CovariantFunctionCast) {
			auto represented = numbers->map(upcast<Ptr<Function<Ptr<Any>, Int>>>(getRepresentation));
			Assert::AreEqual(L"\"1\"::\"2\"::\"3\"::\"4\"::\"5\"::[]", represented->toString()->getRaw().c_str());
		}
	};
}
