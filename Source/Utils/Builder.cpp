#include "Utils/Builder.h"

#include "BasicString.h"


namespace ReLang {
	namespace Utils {
		Ptr<String> makeStringFromBuilder(const std::wostringstream& builder) {
			return Ptr<String>(new String(builder.str()));
		}


		void appendToBuilder(std::wostringstream& builder, Ptr<String> value) {
			if (value) {
				//auto representation = value->toString();
				auto& raw = value->getRaw();
				builder << raw;
			} else {
				builder << L"null";
			}
		}
	}
}
