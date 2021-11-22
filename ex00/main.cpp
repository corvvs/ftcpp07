#include <iostream>
#include <cmath>
#include "whatever.hpp"
#include "Fixed.hpp"
#include "whatever.hpp"
#include "Fixed.hpp"

void    say(const std::string& str) {
    std::cout << str << std::endl;
}

template <class T>
void test(T a, T b) {
    say("(values)");
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    say("(swap)");
    ::swap(a, b);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    say("(min)");
    std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
    say("(max)");
    std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
    say("");
}

int main() {
    {
        say("[ int ]");
        int a = 10;
        int b = 42;
        test(a, b);
        test(a, b);
    }
    {
        say("[ string ]");
        std::string a = "hello";
        std::string b = "world";
        test(a, b);
        test(a, b);
    }
    {
        say("[ const string ]");
        const std::string a = "42";
        const std::string b = "tokyo";
        test(a, b);
        test(a, b);
    }
    {
        say("[ double ]");
        double a = M_PI;
        double b = M_E;
        test(a, b);
        test(a, b);
        double* pa = &a;
        double* pb = &b;
        test(pa, pb);
        test(pa, pb);
        double& ra = a;
        double& rb = b;
        test(ra, rb);
        test(a, b);
    }
    {
        say("[ Fixed @ CPP02 ]");
        Fixed *a = new Fixed(static_cast<float>(M_PI));
        Fixed *b = new Fixed(static_cast<float>(M_E));
        test(*a, *b);
        test(*a, *b);
        delete a;
        delete b;
    }
}
