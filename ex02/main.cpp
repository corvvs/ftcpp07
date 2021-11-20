#include <iostream>
#include <cmath>
#include "Array.hpp"
#include "array_tool.hpp"
#include "Constants.hpp"
#include "Array.hpp"
#include "array_tool.hpp"
#include "Constants.hpp"

void    say(const std::string& str) {
    std::cout << str << std::endl;
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

int main(int argc, char **argv) {
    try {
        say("[ Array<int> ]");
        int n = 10;
        Array<int> int_array(n);
        for (int i = 0; i < n; i += 1) {
            int_array[i] = i + i * i + 1;
        }
        Array<int> int_array2(1);
        std::cout << int_array.getSize() << std::endl;
        std::cout << int_array2.getSize() << std::endl;
        std::cout << int_array[0] << std::endl;
        std::cout << int_array2[0] << std::endl;
        int_array[0] = 42;
        int_array2 = int_array;
        int_array2[0] = 24;
        std::cout << int_array.getSize() << std::endl;
        std::cout << int_array2.getSize() << std::endl;
        std::cout << int_array << std::endl;
        std::cout << int_array2 << std::endl;
        Array<int> int_array3(int_array2);
        std::cout << int_array3.getSize() << std::endl;
        std::cout << int_array3 << std::endl;
        std::cout << std::endl;
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }

    try {
        say("[ Array<string> ]");
        Array<std::string> str_array(argc);
        for(int i = 0; i < argc; i += 1) {
            str_array[i] = argv[i];
        }
        std::cout << str_array << std::endl;

        Array<int> upcased = map(str_array, len);
        std::cout << upcased << std::endl;

        int sl = reduce(str_array, slen);
        std::cout << sl << std::endl;

        str_array.iter(dest_upcase);
        std::cout << str_array << std::endl;

        Array<std::string> str_array2(2);
        std::cout << str_array2 << std::endl;
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }

    try {
        say("[ out of range ]");
        Array<int> array(10);
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
        std::cout << array << std::endl;
        Array<int>* ap = &array;
        *ap = array;
        std::cout << array << std::endl;
        std::cout << *ap << std::endl;
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextError
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}
