#include <iostream>
#include <cmath>
#include "whatever.hpp"
#include "Fixed.hpp"
#include "whatever.hpp"
#include "Fixed.hpp"
#include "Constants.hpp"

void    say(const std::string& str) {
    std::cout << str << std::endl;
}

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

template <class T>
void min_max_test(T& a, T& b) {
    say("(values)");
    std::cout << "a: " << a << "(" << &a << ")" << std::endl;
    std::cout << "b: " << b << "(" << &b << ")" << std::endl;
    const T& ma = ::max(a, b);
    const T& mi = ::min(a, b);
    say("(min)");
    std::cout << "min(a, b) = " << mi << "(" << &mi << ")" << std::endl;
    say("(max)");
    std::cout << "max(a, b) = " << ma << "(" << &ma << ")" << std::endl;
    say("");
}

template <class T>
void test(T& a, T& b) {
    T sa = a;
    T sb = b;
    say("(values)");
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    say("(swap)");
    ::swap(a, b);
    tester("a after swap is", a, sb);
    tester("b after swap is", b, sa);
    min_max_test(a, b);
    const T& ma = ::max(a, b);
    const T& mi = ::min(a, b);
    say("(min)");
    std::cout << "min(a, b) = " << mi << "(" << &mi << ")" << std::endl;
    say("(max)");
    std::cout << "max(a, b) = " << ma << "(" << &ma << ")" << std::endl;
}

int main() {
    {
        say("[ int ]");
        int a = 10;
        int b = 42;
        test(a, b);
        tester("a is", a, 42);
        tester("b is", b, 10);
        test(a, b);
        tester("a is", a, 10);
        tester("b is", b, 42);
        tester("max(a, b) is", ::max(a, b), 42);
        tester("min(a, b) is", ::min(a, b), 10);
    }
    {
        say("[ string ]");
        std::string a = "hello";
        std::string b = "world";
        test(a, b);
        tester("a is", a, std::string("world"));
        tester("b is", b, std::string("hello"));
        tester("max(a, b) is", ::max(a, b), std::string("world"));
        tester("min(a, b) is", ::min(a, b), std::string("hello"));
        test(a, b);
    }
    {
        say("[ double ]");
        double a = M_PI;
        double b = M_E;
        test(a, b);
        test(a, b);
        tester("max(a, b) is", ::max(a, b), M_PI);
        tester("min(a, b) is", ::min(a, b), M_E);
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
        Fixed a(static_cast<float>(M_PI));
        Fixed b(static_cast<float>(M_E));
        test(a, b);
        test(a, b);
    }
    {
        say("[ Same Fixed ]");
        const Fixed a(static_cast<float>(M_PI));
        const Fixed b(a);
        min_max_test(a, b);
        tester("&max(a, b) is &b?", &::max(a, b), &b);
        tester("&min(a, b) is &b?", &::min(a, b), &b);
    }
}
