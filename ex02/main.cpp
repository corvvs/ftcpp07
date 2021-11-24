#include <iostream>
#include <cmath>
#include <sstream>
#include "Array.hpp"
#include "array_tool.hpp"
#include "Constants.hpp"
#include "Array.hpp"
#include "array_tool.hpp"
#include "Constants.hpp"

void    say(const std::string& str) {
    std::cout << str << std::endl;
}

std::stringstream ss;

template <typename Result>
void    tester(
    const std::string& title,
    const Result& result,
    const Result& expected,
    const bool ignorable = false
) {
    bool ok = result == expected;
    const std::string color =
        ok
            ? Constants::kTextInfo
            : ignorable
                ? Constants::kTextWarning
                : Constants::kTextError;
    std::cout
        << color
        << ((result == expected) ? "[ok] " : "[KO] ")
        << title
        << ": "
        << std::boolalpha << result;
    if (!ok) {
        std::cout
            << "(expected: " << expected << ")";
    }
    std::cout
        << Constants::kTextReset << std::endl;
    if (!ok && !ignorable) {
        throw std::string("** detected KO test **");
    }
}

std::string stringify(void) {
    std::string res;
    res = ss.str();
    ss.str("");
    return res;
}

template<class T>
void    put_some(const T& c) {
    std::cout << c << ", ";
}

std::string upcaser(const std::string str) {
    std::string upcased = str;
    for (std::size_t i = 0; i < upcased.length(); i += 1) {
        upcased[i] = std::toupper(str[i]);
    }
    return upcased;
}


void    dest_upcase(std::string& str) {
    for (std::size_t i = 0; i < str.length(); i += 1) {
        str[i] = std::toupper(str[i]);
    }
}

int len(const std::string str) {
    return str.length();
}

int slen(int s, const std::string str) {
    return s + str.length();
}

bool is_hello(std::string& str) {
    return str == "hello";
}

int main(int argc, char **argv) {
    try {
        say("[ Array<int> ]");
        unsigned int n = 10;
        Array<int> int_array(n);
        for (unsigned i = 0; i < n; i += 1) {
            int_array[i] = i + i * i + 1;
        }
        Array<int> int_array2(1);
        tester("size of int_array(10)", int_array.getSize(), n);
        tester("int_array[0]", int_array[0], 1);
        tester("size of int_array2(1)", int_array2.getSize(), 1u);
        tester("int_array2[0]", int_array2[0], 0);
        int_array[0] = 42;
        int_array2 = int_array;
        int_array2[0] = 24;
        say("int_array[0] = 42, int_array2 = int_array, int_array2[0] = 24");
        tester("size of int_array", int_array.getSize(), n);
        tester("size of int_array2", int_array2.getSize(), n);
        ss << int_array;
        tester("int_array", stringify(), std::string("[42, 3, 7, 13, 21, 31, 43, 57, 73, 91]"));
        ss << int_array2;
        tester("int_array2", stringify(), std::string("[24, 3, 7, 13, 21, 31, 43, 57, 73, 91]"));
        say("int_array3 is cloned from int_array2");
        Array<int> int_array3(int_array2);
        tester("size of int_array3", int_array3.getSize(), n);
        ss << int_array3;
        tester("int_array3", stringify(), std::string("[24, 3, 7, 13, 21, 31, 43, 57, 73, 91]"));
        say("int_array4 is cloned from int_array");
        const Array<int> int_array4(int_array);
        tester("size of int_array4", int_array3.getSize(), n);
        ss << int_array4;
        tester("int_array4", stringify(), std::string("[42, 3, 7, 13, 21, 31, 43, 57, 73, 91]"));
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }

    try {
        say("[ Array<string> ]");
        Array<std::string> str_array(argc - 1);
        for(int i = 1; i < argc; i += 1) {
            str_array[i - 1] = argv[i];
        }
        std::cout << str_array << std::endl;

        std::cout
            << "any hello?: "
            << std::boolalpha << any(str_array, is_hello)
            << std::endl;
        std::cout
            << "every hello?: "
            << std::boolalpha << every(str_array, is_hello)
            << std::endl;

        Array<int> upcased = map(str_array, len);
        std::cout << upcased << std::endl;

        int sl = reduce(str_array, slen);
        std::cout << sl << std::endl;

        str_array.iter(dest_upcase);
        std::cout << str_array << std::endl;

        Array<std::string> str_array2(2);
        std::cout << str_array2 << std::endl;

        Array<std::string> str_array3(0);
        std::cout << str_array3 << std::endl;
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }

    try {
        say("[ out of range ]");
        Array<int> array(10);
        say("reading index 10 from size-10 array, it will cause EXCEPTION");
        std::cout << array[10] << std::endl;
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }

    try {
        say("[ self assignation ]");
        Array<int> array = Array<int>(10);
        array[0] = 100;
        array[9] = -42;
        ss << array;
        tester("array", stringify(), std::string("[100, 0, 0, 0, 0, 0, 0, 0, 0, -42]"));
        Array<int>* ap = &array;
        say("ap = &array");
        say("*ap = array (self assignation)");
        ss << array;
        tester("array", stringify(), std::string("[100, 0, 0, 0, 0, 0, 0, 0, 0, -42]"));
        ss << *ap;
        tester("ap", stringify(), std::string("[100, 0, 0, 0, 0, 0, 0, 0, 0, -42]"));
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}
