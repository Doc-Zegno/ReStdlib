#include "Utils/StringUtils.h"

#include "BasicString.h"


namespace ReLang {
    namespace Utils {
        Ptr<String> makeStringFromBuilder(const std::wostringstream& builder) {
            return Ptr<String>(new String(builder.str()));
        }


        Ptr<String> join(const Char* separator, Ptr<Iterable<Ptr<Any>>> items, const Char* prefix, const Char* suffix) {
            auto builder = std::wostringstream();
            builder << prefix;
            auto iterator = items->getIterator();
            auto isFirst = true;
            while (iterator->moveNext()) {
                if (!isFirst) {
                    builder << separator;
                }
                auto current = iterator->getCurrent();
                if (current) {
                    auto representation = current->toString();
                    auto& raw = representation->getRaw();
                    builder << raw;
                } else {
                    builder << L"null";
                }
                isFirst = false;
            }
            builder << suffix;
            return Ptr<String>(new String(builder.str()));
        }
    }
}