#ifndef MATRIX_RATIONALS_H
#define MATRIX_RATIONALS_H

#include <iostream>

template<typename I>
I gcd(I a, I b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

template<typename I>
class Rational {
private:
    I num;
    I denom;
public:
    explicit Rational(const I &&n) : num(n), denom(1) {}

    Rational(const I &&n, const I &&d) : num(n / gcd(n, d)), denom(d / gcd(n, d)) {}

    bool operator==(const Rational &other) const {
        return num == other.num && denom == other.denom;
    }

    friend std::ostream &operator<<(std::ostream &os, Rational<I> r) {
        os << r.num;
        if (r.denom != 1)
            os << "/" << r.denom;
        return os;
    }
};


#endif //MATRIX_RATIONALS_H
