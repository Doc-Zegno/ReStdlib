#include "stdafx.h"
#include "CppUnitTest.h"

#include "BasicString.h"
#include "Utils/Format.h"
#include "Utils/Escape.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ReLang;


namespace UnitTestProject {
	TEST_CLASS(StringUtilsTest) {
	public:
		TEST_METHOD(Format) {
			Assert::AreEqual(L"(-3; -4)", Utils::format(L'(', -3, L"; ", -4, L')')->getRaw().c_str());
		}


		TEST_METHOD(EscapeString) {
			auto string = L"{\n\t\"text\": \"Hello, World!\";\n\t\"number\": 5;\n\t\"char\": 'A'\n}";
			Char destination[100] = { 0 };
			auto end = Utils::escapeString(string, destination);
			auto expected = L"{\\n\\t\\\"text\\\": \\\"Hello, World!\\\";\\n\\t\\\"number\\\": 5;\\n\\t\\\"char\\\": 'A'\\n}";
			//Logger::WriteMessage(destination);
			Assert::AreEqual(expected, destination);
		}
	};
}