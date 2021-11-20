#include "Fixed.hpp"
#include <cmath>

// ** utils **
bool    Fixed::WillAdditionOverflow(const Fixed& lhs, const Fixed& rhs) {
    int a = lhs.getRawBits();
    int b = rhs.getRawBits();
    if (a > 0 && b > 0 && a > INT_MAX - b) {
        return true;
    }
    if (a < 0 && b < 0 && a < INT_MIN - b) {
        return true;
    }
    return false;
}

bool    Fixed::WillSubtractionOverflow(const Fixed& lhs, const Fixed& rhs) {
    int a = lhs.getRawBits();
    int b = rhs.getRawBits();
    if (a > 0 && b < 0 && a > INT_MAX + b) {
        return true;
    }
    if (a < 0 && b > 0 && a < INT_MIN + b) {
        return true;
    }
    return false;
}

Fixed::Fixed(): bits_(0) {
    std::cout << "DEFCON" << std::endl;
}

Fixed::Fixed(int const val){
    int shifted = val << Fixed::kFractionalBits;
    int reshifted = shifted >> Fixed::kFractionalBits;
    if (val != reshifted) {
        bits_ = val > 0 ? INT_MAX : INT_MIN;
    } else {
        bits_ = shifted;
    }
}

Fixed::Fixed(float const val){
    double fb2 = (double)(1 << Fixed::kFractionalBits);
    double pval = val * fb2;
    if (pval >= INT_MAX) {
        bits_ = INT_MAX;
    } else if (pval <= INT_MIN) {
        bits_ = INT_MIN;
    } else {
        bits_ = roundf(pval);
    }
}

Fixed::~Fixed() {}

Fixed::Fixed(const Fixed &from): bits_(from.getRawBits()) {}

Fixed &Fixed::operator=(const Fixed &rhs) {
    bits_ = rhs.getRawBits();
    return *this;
}

int Fixed::getRawBits(void) const {
    return bits_;
}

void    Fixed::setRawBits(int const raw) {
    bits_ = raw;
}

int     Fixed::toInt(void) const {
    return bits_ >> Fixed::kFractionalBits;
}
float   Fixed::toFloat(void) const {
    double fb2 = (double)(1 << Fixed::kFractionalBits);
    return bits_ / fb2;
}

Fixed   Fixed::abs(void) const {
    return *this >= 0 ? Fixed(*this) : Fixed(0) - *this;
}

Fixed&  Fixed::min(Fixed& f1, Fixed& f2) {
    return (f1 < f2) ? f1 : f2;
}

const Fixed&    Fixed::min(const Fixed& f1, const Fixed& f2) {
    return (f1 < f2) ? f1 : f2;
}

Fixed&  Fixed::max(Fixed& f1, Fixed& f2) {
    return (f1 > f2) ? f1 : f2;
}

const Fixed&    Fixed::max(const Fixed& f1, const Fixed& f2) {
    return (f1 > f2) ? f1 : f2;
}

// ** increment / decrement operators **
// prefix ++
Fixed& Fixed::operator++() {
    if (bits_ < INT_MAX) {
        bits_ += 1;
    }
    return *this;
}

// prefix --
Fixed& Fixed::operator--() {
    if (bits_ > INT_MIN) {
        bits_ -= 1;
    }
    return *this;
}

// postfix ++
Fixed Fixed::operator++(int _) {
    (void)_;
    Fixed rv(*this);
    ++*this;
    return rv;
}

// postfix --
Fixed Fixed::operator--(int _) {
    (void)_;
    Fixed rv(*this);
    --*this;
    return rv;
}

// ** stream-out operator **
std::ostream& operator<<(std::ostream& stream, const Fixed& value) {
    return stream << value.toFloat();
}

// ** comparison operators **
bool operator<(const Fixed& lhs, const Fixed& rhs) {
    return lhs.getRawBits() < rhs.getRawBits();
}

bool operator>(const Fixed& lhs, const Fixed& rhs) {
    return lhs.getRawBits() > rhs.getRawBits();
}

bool operator==(const Fixed& lhs, const Fixed& rhs) {
    return lhs.getRawBits() == rhs.getRawBits();
}

bool operator!=(const Fixed& lhs, const Fixed& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Fixed& lhs, const Fixed& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>=(const Fixed& lhs, const Fixed& rhs) {
    return (lhs > rhs) || (lhs == rhs);
}

// ** arithmeic operators **
Fixed operator+(const Fixed& lhs, const Fixed& rhs) {
    Fixed r;
    if (Fixed::WillAdditionOverflow(lhs, rhs)) {
        if (rhs.getRawBits() > 0) {
            r.setRawBits(INT_MAX);
        } else {
            r.setRawBits(INT_MIN);
        }
    } else {
        r.setRawBits(lhs.getRawBits() + rhs.getRawBits());
    }
    return r;
}

Fixed operator-(const Fixed& lhs, const Fixed& rhs) {
    Fixed r;
    if (Fixed::WillSubtractionOverflow(lhs, rhs)) {
        if (rhs.getRawBits() > 0) {
            r.setRawBits(INT_MIN);
        } else {
            r.setRawBits(INT_MAX);
        }
    } else {
        r.setRawBits(lhs.getRawBits() - rhs.getRawBits());
    }
    return r;
}

Fixed operator*(const Fixed& lhs, const Fixed& rhs) {
    Fixed r;
    r.setRawBits((lhs.getRawBits() * rhs.getRawBits()) >> Fixed::kFractionalBits);
    return r;
}

Fixed operator/(const Fixed& lhs, const Fixed& rhs) {
    Fixed r;
    r.setRawBits((lhs.getRawBits() << Fixed::kFractionalBits) / rhs.getRawBits());
    return r;
}

