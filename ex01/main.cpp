#include <iostream>
#include <cmath>
#include "iter.hpp"
#include "iter.hpp"
#include "Fixed.hpp"

void    say(const std::string& str) {
    std::cout << std::endl << str << std::endl << std::endl;
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
        say("<4, put_some>");
        iter(array, 4, put_some);
        std::cout << std::endl;
    }
    {
        say("[ int[] ]");
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
        say("[ const char* ]");
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
        say("[ char* ]");
        char var[8];
        memcpy(var, "42tokyo\n", 8);
        say("<8, put_some>");
        iter(var, 8, put_some);
        say("<8, put_any>");
        iter(var, 8, put_any);
        char* var2 = NULL;
        say("<NULL>");
        iter(var2, 8, put_any);
    }
    {
        say("[ std::string[] ]");
        iter(argv, argc, put_any);
        std::cout << std::endl;
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
        std::cout << std::endl;
        iter(strs, n, doubler);
        iter(strs, n, put_any);
        std::cout << std::endl;
    }
    {
        say("[ Fixed ]");
        Fixed fs1[2];
        fs1[0] = Fixed(1.2f);
        fs1[1] = Fixed(3.456f);
        const Fixed fs2[2] = { fs1[0], fs1[1] };
        iter(fs1, 2, prnt_byref);
        iter(fs1, 2, doubler);
        iter(fs1, 2, prnt_byref);
        iter(fs2, 2, prnt_byref);
    }
    {
        say("[ special ]");
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
