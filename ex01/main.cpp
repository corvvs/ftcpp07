#include <iostream>
#include <cmath>
#include "iter.hpp"
#include "iter.hpp"
#include "Fixed.hpp"
#include "Constants.hpp"
#include <sstream>

void    say(const std::string& str) {
    std::cout << std::endl << str << std::endl << std::endl;
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

void    put_char(const char& c) {
    ss << c;
}

void    put_int(const int c) {
    ss << c << ", ";
}

template<class T>
void    put_some(T& c) {
    ss << c << ", ";
}

template<class T>
void    put_some(const T& c) {
    ss << c << ", ";
}

template<>
void    put_some(const char& c) {
    ss << c;
}

template<class T>
void    put_any(T& c) {
    ss << c << ", ";
}

template<>
void    put_any(char& c) {
    ss << c;
}

template<>
void    put_any(const char& c) {
    ss << c;
}

template<class T>
void    doubler(T& n) {
    n = n + n;
}

template<class T>
void    prnt_byref(T const & n) {
    std::cout << "[" << n << "]" << std::endl;
}

template<class T>
void    prnt_byref_var(T & n) {
    std::cout << "[" << n << "]" << std::endl;
}

template<class T>
void    prnt_byval(T const n) {
    std::cout << "[" << n << "]" << std::endl;
}

template<class T>
void    prnt_byval_var(T n) {
    std::cout << "[" << n << "]" << std::endl;
}

int main(int argc, char **argv) {
    {
        say("[ const int[] ]");
        const int array[] = {3, 2, 1, 0};
        iter(array, 4, put_some);
        tester("array is", stringify(), std::string("3, 2, 1, 0, ")); 
    }
    {
        say("[ int[] ]");
        int array2[] = {5, 6, 7, 8};
        iter(array2, 4, put_some);
        tester("array2", stringify(), std::string("5, 6, 7, 8, "));

        iter(array2, 4, doubler);
        iter(array2, 4, put_some);
        tester("after <4, doubler>", stringify(), std::string("10, 12, 14, 16, "));
        say("<2, doubler>");
        iter(array2, 2, doubler);
        iter(array2, 4, put_some);
        tester("after <2, doubler>", stringify(), std::string("20, 24, 14, 16, "));
    }
    void (*fchar)(const char& c) = put_char;
    {
        say("[ const char* ]");
        iter("42tokyo!", 8, fchar);
        tester("iter(\"42tokyo!\", 8, fchar)", stringify(), std::string("42tokyo!"));
        fchar = NULL;
        iter("42tokyo!", 8, fchar);
        tester("iter(\"42tokyo!\", 8, NULL)", stringify(), std::string(""));
        iter("42tokyo!", 8, put_some);
        tester("iter(\"42tokyo!\", 8, put_some)", stringify(), std::string("42tokyo!"));
        iter("42tokyo!", 8, put_any);
        tester("iter(\"42tokyo!\", 8, put_any)", stringify(), std::string("42tokyo!"));
        iter("42tokyo!", 8, put_any<const char>);
        tester("iter(\"42tokyo!\", 8, put_any<char>)", stringify(), std::string("42tokyo!"));

        say("[ char* ]");
        char var[8];
        memcpy(var, "42tokyo!", 8);
        iter(var, 8, put_some);
        tester("iter(\"42tokyo!\", 8, put_some)", stringify(), std::string("4, 2, t, o, k, y, o, !, "));
        iter(var, 8, put_any);
        tester("iter(\"42tokyo!\", 8, put_any<char>)", stringify(), std::string("42tokyo!"));
        char* var2 = NULL;
        iter(var2, 8, put_any);
        tester("iter(NULL, 8, put_any)", stringify(), std::string(""));
    }
    {
        say("[ std::string[] ]");
        iter(argv, argc, put_any);
        std::cout << stringify() << std::endl;
        const int n = 4;
        std::string strs[n];
        for (int i = 0; i < n; i += 1) {
            if (i < argc) {
                strs[i] = argv[i];
            } else {
                strs[i] = "";
            }
        }
        iter(strs, n, put_any);
        std::cout << stringify() << std::endl;
        iter(strs, n, doubler);
        iter(strs, n, put_any);
        std::cout << stringify() << std::endl;
    }
    {
        say("[ Fixed ]");
        Fixed fs1[2];
        fs1[0] = Fixed(1.2f);
        fs1[1] = Fixed(3.456f);
        const Fixed fs2[2] = { fs1[0], fs1[1] };
        iter(fs1, 2, prnt_byref);
        std::cout << stringify() << std::endl;
        iter(fs1, 2, doubler);
        iter(fs1, 2, prnt_byref);
        std::cout << stringify() << std::endl;
        iter(fs2, 2, prnt_byref);
        std::cout << stringify() << std::endl;
    }
    {
        say("[ special ]");
        say("** checking only is it compilable **");
        int is1[] = { 1, 2, 3, 10 };
        const int is2[] = { 3, 2, 1, -10 };
        std::cout << "- is1: byref_const -" << std::endl;
        iter(is1, 4, prnt_byref);
        std::cout << "- is1: byref_var -" << std::endl;
        iter(is1, 4, prnt_byref_var);
        std::cout << "- is1: byval_const -" << std::endl;
        iter(is1, 4, prnt_byval);
        std::cout << "- is1: byval_var -" << std::endl;
        iter(is1, 4, prnt_byval_var);
        std::cout << "(is1 is doubled)" << std::endl;
        iter(is1, 4, doubler);
        std::cout << "- is1: byref_const -" << std::endl;
        iter(is1, 4, prnt_byref);
        std::cout << "- is1: byref_var -" << std::endl;
        iter(is1, 4, prnt_byref_var);
        std::cout << "- is1: byval_const -" << std::endl;
        iter(is1, 4, prnt_byval);
        std::cout << "- is1: byval_var -" << std::endl;
        iter(is1, 4, prnt_byval_var);
        std::cout << "- is2: byref_const -" << std::endl;
        iter(is2, 4, prnt_byref);
        std::cout << "- is2: byref_var -" << std::endl;
        iter(is2, 4, prnt_byref_var);
        std::cout << "- is2: byval_const -" << std::endl;
        iter(is2, 4, prnt_byval);
        std::cout << "- is2: byval_var -" << std::endl;
        iter(is2, 4, prnt_byval_var);
        // iter(is2, 4, doubler); // error: cannot assign to variable 'n' with const-qualified type 'const int &'
    }
    {
        say("[ special2 ]");
        say("** checking only is it compilable **");
        char str1[] = "mahimahi\n";
        std::cout << "- byref -" << std::endl;
        iter(str1, 9, prnt_byref);
        std::cout << "- byval -" << std::endl;
        iter(str1, 9, prnt_byval);
        std::cout << "- byref_var -" << std::endl;
        iter(str1, 9, prnt_byref_var);
        std::cout << "- byval_var -" << std::endl;
        iter(str1, 9, prnt_byval_var);
        std::cout << "- byref instantiated -" << std::endl;
        iter(str1, 9, prnt_byref<const char&>);
        // iter(str1, 9, prnt_byval<const char>); // error: no matching function for call to 'iter'
        std::cout << "- byref_var instantiated -" << std::endl;
        iter(str1, 9, prnt_byref_var<char&>);
        // iter(str1, 9, prnt_byval_var<char>); // error: no matching function for call to 'iter'
    }
}
