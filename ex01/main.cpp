#include <iostream>
#include <cmath>
#include "iter.hpp"
#include "iter.hpp"

void    say(const std::string& str) {
    std::cout << str << std::endl;
}

void    put_char(const char c) {
    std::cout << c;
}

void    put_int(const int c) {
    std::cout << c << ", ";
}

template<class T>
void    put_some(const T& c) {
    std::cout << c << ", ";
}

template<>
void    put_some(const char& c) {
    std::cout << c;
}

int main(int argc, char **argv) {

    void (*fchar)(const char c) = put_char;
    {
        say("[ std::string ]");
        say("<8, fchar>");
        iter("42tokyo\n", 8, fchar);
        say("<0, fchar>");
        iter("42tokyo\n", 0, fchar);
        fchar = NULL;
        say("<8, NULL>");
        iter("42tokyo\n", 8, fchar);
        say("<8, put_int>");
        iter("42tokyo\n", 8, put_int);
        std::cout << std::endl;
        say("<8, put_some<char>>");
        iter("42tokyo\n", 8, put_some<char>);
        say("<8, put_some<int>>");
        iter("42tokyo\n", 8, put_some<int>);
        std::cout << std::endl;
        say("<8, put_some<double>>");
        iter("42tokyo\n", 8, put_some<double>);
        std::cout << std::endl;
    }
    {
        say("[ std::string[] ]");
        iter(argv, argc, put_some<std::string>);
        std::cout << std::endl;
    }
}
