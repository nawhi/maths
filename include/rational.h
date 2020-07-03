#ifndef MATRIX_RATIONALS_H
#define MATRIX_RATIONALS_H


template <typename I>
class Rational {
private:
    int num;
    int denom;
public:
    explicit Rational(const int&& n): num(n), denom(1) {}

    bool operator == (const Rational& other) const {
        return num == other.num && denom == other.denom;
    }
};


#endif //MATRIX_RATIONALS_H
