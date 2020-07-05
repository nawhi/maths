#ifndef MATHS_FRACTION_H
#define MATHS_FRACTION_H

#include <iostream>

namespace fractions {

    template<typename I>
    I greatest_common_divisor(I a, I b) {
        if (b == 0) return a;
        return greatest_common_divisor(b, a % b);
    }

    template<typename I>
    I abs(I i) {
        return i < 0 ? -i : i;
    }

    template<typename I>
    I lowest_common_multiple(I a, I b) {
        return (abs(a) / greatest_common_divisor(a, b)) * b;
    }

    class division_by_zero : std::exception {
    };

    template<typename I>
    class Fraction {
    public:
        explicit Fraction(const I numerator, const I denominator = 1) {
            if (denominator == 0) {
                throw division_by_zero();
            }
            I gcd = greatest_common_divisor(numerator, denominator);
            num = numerator / gcd;
            denom = denominator / gcd;
        }

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

        Fraction operator/(const I &other) const {
            return div(other);
        }

        Fraction operator/(const Fraction &other) const {
            return div(other);
        }

        Fraction operator+(const Fraction &other) const {
            return plus(other);
        }

        Fraction operator+(const I &other) const {
            return plus(other);
        }

        friend Fraction operator+(const I &lhs, const Fraction &rhs) {
            return rhs.plus(lhs);
        }

        Fraction operator+() {
            return *this;
        }

        Fraction operator-(const Fraction &other) const {
            return minus(other);
        }

        Fraction operator-(const I &i) const {
            return minus(i);
        }

        Fraction operator-() {
            return Fraction(-num, denom);
        }

        bool operator>(const Fraction &other) const {
            return gt(other);
        }

        bool operator>(const I &i) const {
            return num > i * denom;
        }

        bool operator>=(const Fraction &other) const {
            return *this == other || *this > other;
        }

        bool operator>=(const I &i) const {
            return *this == i || *this > i;
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

        Fraction plus(const Fraction &other) const {
            const I lcm = lowest_common_multiple(denom, other.denom);
            const I new_num = num * (lcm / denom) + other.num * (lcm / other.denom);
            return Fraction(new_num, denom * lcm / denom);
        }

        Fraction plus(const I &other) const {
            return Fraction(num + other * denom, denom);
        }

        Fraction minus(const Fraction &other) const {
            const I lcm = lowest_common_multiple(denom, other.denom);
            const I new_num = num * (lcm / denom) - other.num * (lcm / other.denom);
            return Fraction(new_num, denom * lcm / denom);
        }

        Fraction minus(const I &other) const {
            return Fraction(num - other * denom, denom);
        }

        bool gt(const Fraction &other) const {
            const I lcm = lowest_common_multiple(denom, other.denom);
            return num * (lcm / denom) > other.num * (lcm / other.denom);
        }

        bool lt(const Fraction &other) const {
            const I lcm = lowest_common_multiple(denom, other.denom);
            return num * (lcm / denom) < other.num * (lcm / other.denom);
        }
    };

}
#endif //MATHS_FRACTION_H
