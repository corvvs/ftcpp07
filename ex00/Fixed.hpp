#ifndef CPP02_EX03_FIXED_HPP_
# define CPP02_EX03_FIXED_HPP_

# include <iostream>

class Fixed {
    public:
        static const int    kFractionalBits = 8;
        Fixed();
        Fixed(int const val);
        Fixed(float const val);
        ~Fixed();
        Fixed(const Fixed &from);
        Fixed& operator=(const Fixed &rhs);

        int     getRawBits(void) const;
        void    setRawBits(int const raw);
        int     toInt(void) const;
        float   toFloat(void) const;
        Fixed   abs(void) const;


        Fixed& operator++();
        Fixed& operator--();
        Fixed operator++(int);
        Fixed operator--(int);

        static bool WillAdditionOverflow(const Fixed& lhs, const Fixed& rhs);
        static bool WillSubtractionOverflow(const Fixed& lhs, const Fixed& rhs);
        static Fixed&   min(Fixed& f1, Fixed& f2);
        static const Fixed& min(const Fixed& f1, const Fixed& f2);
        static Fixed&   max(Fixed& f1, Fixed& f2);
        static const Fixed& max(const Fixed& f1, const Fixed& f2);

    private:
        int                 bits_;
};

std::ostream& operator<<(std::ostream& stream, const Fixed& value);

bool operator<(const Fixed& lhs, const Fixed& rhs);
bool operator>(const Fixed& lhs, const Fixed& rhs);
bool operator==(const Fixed& lhs, const Fixed& rhs);
bool operator!=(const Fixed& lhs, const Fixed& rhs);
bool operator<=(const Fixed& lhs, const Fixed& rhs);
bool operator>=(const Fixed& lhs, const Fixed& rhs);

Fixed operator+(const Fixed& lhs, const Fixed& rhs);
Fixed operator-(const Fixed& lhs, const Fixed& rhs);
Fixed operator*(const Fixed& lhs, const Fixed& rhs);
Fixed operator/(const Fixed& lhs, const Fixed& rhs);

#endif
