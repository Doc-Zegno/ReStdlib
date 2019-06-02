#pragma once

#include "Primitives.h"


namespace ReLang {
	namespace Utils {
		Char* escapeChar(Char ch, Char* destination, Bool isSingleQuoteEscaped);
		Char* escapeString(const Char* string, Char* destination);
	}
}
