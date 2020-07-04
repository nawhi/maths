#ifndef MATRIX_RATIONALS_H
#define MATRIX_RATIONALS_H

#include <iostream>

template<typename I>
I gcd(I a, I b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

template<typename I>
class Fraction {
public:
    explicit Fraction(const I n, const I d = 1) : num(n / gcd(n, d)), denom(d / gcd(n, d)) {}

    bool operator==(const Fraction &other) const {
        return num == other.num && denom == other.denom;
    }

    bool operator==(const I &i) const {
        return denom == 1 && num == i;
    }

    friend bool operator==(const I &lhs, const Fraction &rhs) {
        return rhs == lhs;
    }

    friend bool operator!=(const I &lhs, const Fraction &rhs) {
        return rhs != lhs;
    }

    bool operator!=(const Fraction &other) const { return !(*this == other); }

    bool operator!=(const I &i) const { return !(*this == i); }

    Fraction operator*(const I &other) const {
        return times(other);
    }

    Fraction operator*(const Fraction &other) const {
        return times(other);
    }

    friend Fraction operator*(const I &lhs, const Fraction rhs) {
        return rhs.times(lhs);
    }

    Fraction operator/(const I& other) const {
        return div(other);
    }

    Fraction operator/(const Fraction& other) const {
        return div(other);
    }

    friend std::ostream &operator<<(std::ostream &os, Fraction<I> r) {
        os << r.num;
        if (r.denom != 1)
            os << "/" << r.denom;
        return os;
    }

private:
    I num;
    I denom;

    Fraction times(const I &other) const {
        return Fraction(num * other, denom);
    }

    Fraction times(const Fraction &other) const {
        return Fraction(num * other.num, denom * other.denom);
    }

    Fraction div(const I &other) const {
        return Fraction(num, denom * other);
    }

    Fraction div(const Fraction &other) const {
        return Fraction(num * other.denom, denom * other.num);
    }
};


#endif //MATRIX_RATIONALS_H
