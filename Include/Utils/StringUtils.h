#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <iostream>
#include <sstream>
#include <cstring>


#include "../Any.h"
#include "../Primitives.h"
#include "../Iterable.h"


namespace ReLang {
    class String;


    namespace Utils {
        Ptr<String> makeStringFromBuilder(const std::wostringstream& builder);


        template<typename T>
        Ptr<String> join(const Char* separator, Ptr<Iterable<T>> items, const Char* prefix = L"", const Char* suffix = L"") {
            auto builder = std::wostringstream(prefix);
            auto iterator = items->getIterator();
            auto isFirst = true;
            while (iterator->moveNext()) {
                auto current = iterator->getCurrent();
                if (!isFirst) {
                    builder << separator;
                }
                builder << current;
                isFirst = false;
            }
            builder << suffix;
            return makeStringFromBuilder(builder);
        }


        Ptr<String> join(const Char* separator, Ptr<Iterable<Ptr<Any>>> items, const Char* prefix = L"", const Char* suffix = L"");


        template<typename T>
        Ptr<String> join(const Char* separator, Ptr<Iterable<Ptr<T>>> items, const Char* prefix = L"", const Char* suffix = L"") {
            auto ptr = std::reinterpret_pointer_cast<Iterable<Ptr<Any>>>(items);
            return join(separator, ptr, prefix, suffix);
        }


        /// <summary>
        /// Provides functionality for building formatted strings
        /// </summary>
        /*class StringFormatter {
        private:
            static void raiseException(const std::wstring& message)
            {
                throw Error(
                    Ptr<String>(new String(std::wstring(L"StringFormatter failure: ") + message))
                );
            }


            template<typename T>
            static void inject(std::ostream& out, const T& value, const char* options)
            {
                out << value;
            }


            template<typename T, typename... TArgs>
            static void step(std::ostream& out, char* pattern, const T& value, const TArgs&... args)
            {
                auto p = std::strchr(pattern, '{');
                if (!p) {
                    raiseException("placeholder {} wasn't found");
                }

                auto q = std::strchr(p + 1, '}');
                if (!q) {
                    raiseException("closing braces } weren't found");
                }

                *p = '\0';
                *q = '\0';
                out << pattern;
                inject(out, value, p + 1);

                step(out, q + 1, args...);
            }


            static void step(std::ostream& out, char* pattern)
            {
                auto p = std::strchr(pattern, '{');
                if (p) {
                    raiseException("opening braces { were found but no arguments were provided");
                }
                out << pattern;
            }


            std::string _pattern;

        public:
            /// <param name="pattern">
            ///     Pattern of string to be built
            ///     <para>
            ///         **Example**: pattern "({}, {}, {})" and values 1, 2, 3 will produce
            ///         "(1, 2, 3)"
            ///     </para>
            ///     <para>
            ///         **Note**: use {:x} for hex
            ///     </para>
            /// </param>
            StringFormatter(const std::string& pattern) : _pattern(pattern) { }


            /// <summary>
            /// Build string using stored pattern and input values.
            /// </summary>
            /// <param name="args">Values to be injected into output string</param>
            /// <returns>Copy of pattern string with injected values</returns>
            template<typename... TArgs>
            std::string format(const TArgs&... args)
            {
                auto sout = std::ostringstream();
                auto size = _pattern.size() + 1;
                auto buffer = std::unique_ptr<char[]>(new char[size]);
                std::memcpy(buffer.get(), _pattern.c_str(), size);
                step(sout, buffer.get(), args...);
                return sout.str();
            }
        };



        /// <summary>
        /// Shorthand for `StringFormatter(pattern)`
        /// </summary>
        inline StringFormatter operator"" _sf(const char* pattern, size_t size) {
            return StringFormatter(std::string(pattern, size));
        }*/
    }
}


#endif
