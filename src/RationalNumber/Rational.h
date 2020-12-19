//
// Created by Nik Carlson on 18.12.2020.
//

#ifndef COMPUTERALGEBRATASK_RATIONAL_H
#define COMPUTERALGEBRATASK_RATIONAL_H

#include <string>

typedef long double ld;

class Rational {
private:
    ld numerator;
    ld denominator;
public:
    Rational();

    explicit Rational(ld, ld denominator = 1.0L);

    std::string to_str() const;

    bool operator==(const Rational &right) const {
        return this == &right;
    }

    Rational &operator=(const Rational &right) {
        if (this == &right) {
            return *this;
        }
        numerator = right.numerator;
        denominator = right.denominator;
        return *this;
    }

    explicit operator long double() const {
        return (this->numerator) / (this->denominator);
    }

    friend Rational operator+(const Rational &left, const Rational &right);

    friend Rational &operator+(Rational &left, const Rational &right);

    friend Rational operator-(const Rational &left, const Rational &right);

    friend Rational &operator-(Rational &left, const Rational &right);

    friend Rational operator*(const Rational &left, const Rational &right);

    friend Rational &operator*(Rational &left, const Rational &right);

    friend Rational operator/(const Rational &left, const Rational &right);

    friend Rational &operator/(Rational &left, const Rational &right);

};


#endif //COMPUTERALGEBRATASK_RATIONAL_H
