#include "Utils/Escape.h"


namespace ReLang {
	namespace Utils {
		Char* escapeChar(Char ch, Char* destination, Bool isSingleQuoteEscaped) {
			auto isEscaped = true;
			*destination = L'\\';

			Char injected;
			switch (ch) {
			case L'\n':
				injected = L'n';
				break;

			case L'\t':
				injected = L't';
				break;

			case L'\r':
				injected = L'r';
				break;

			case L'\b':
				injected = L'b';
				break;

			case L'\a':
				injected = L'a';
				break;

			case L'\f':
				injected = L'f';
				break;

			case L'\v':
				injected = L'v';
				break;

			case L'\'':
				injected = L'\'';
				isEscaped = isSingleQuoteEscaped;
				break;

			case L'\"':
				injected = L'\"';
				break;

			case L'\\':
				injected = L'\\';
				break;

			case L'\0':
				injected = L'0';
				break;

			default:
				injected = ch;
				isEscaped = false;
				break;
			}

			auto nextPosition = isEscaped ? destination + 1 : destination;
			*nextPosition = injected;
			return nextPosition + 1;
		}


		Char* escapeString(const Char* string, Char* destination) {
			auto p = string;
			auto q = destination;
			while (*p != L'\0') {
				q = escapeChar(*p, q, false);
				p++;
			}
			//*q = *p;
			return q;
		}
	}
}
