#include <iostream>
#include <cmath>
#include "iter.hpp"
#include "iter.hpp"

void    say(const std::string& str) {
    std::cout << str << std::endl;
}

void    put_char(const char& c) {
    std::cout << c;
}

void    put_int(const int c) {
    std::cout << c << ", ";
}

template<class T>
void    put_some(T& c) {
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

template<class T>
void    put_any(T& c) {
    std::cout << c << ", ";
}

template<>
void    put_any(char& c) {
    std::cout << c;
}

template<>
void    put_any(const char& c) {
    std::cout << c;
}

void    doubler(int& n) {
    n *= 2;
}


int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    {
        say("[ int[] ]");
        const int array[] = {3, 2, 1, 0};
        say("<4, put_some>");
        iter(array, 4, put_some);
        std::cout << std::endl;
    }
    {
        say("[ const int[] ]");
        int array2[] = {5, 6, 7, 8};
        say("<4, put_some>");
        iter(array2, 4, put_some);
        std::cout << std::endl;
        say("<4, doubler>");
        iter(array2, 4, doubler);
        iter(array2, 4, put_some);
        std::cout << std::endl;
        say("<2, doubler>");
        iter(array2, 2, doubler);
        iter(array2, 4, put_some);
        std::cout << std::endl;
    }
    void (*fchar)(const char& c) = put_char;
    {
        say("[ std::string ]");
        say("<8, fchar>");
        iter("42tokyo\n", 8, fchar);
        say("<8, fchar=NULL>");
        fchar = NULL;
        iter("42tokyo\n", 8, fchar);
        say("<8, put_some>");
        iter("42tokyo\n", 8, put_some);
        say("<8, put_any>");
        iter("42tokyo\n", 8, put_any);
        say("<8, put_any<char>>");
        iter("42tokyo\n", 8, put_any<const char>);
        char var[8];
        memcpy(var, "42tokyo\n", 8);
        say("<8, put_some>");
        iter(var, 8, put_some);
        say("<8, put_any>");
        iter(var, 8, put_any);
    }
    {
        say("[ std::string[] ]");
        iter(argv, argc, put_any);
        std::cout << std::endl;
    }
}
