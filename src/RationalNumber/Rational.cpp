//
// Created by Nik Carlson on 18.12.2020.
//

#include "Rational.h"

Rational::Rational(ld numerator, ld denominator) : numerator(numerator), denominator(denominator) {
}

std::string Rational::to_str() const {
    if (denominator != 1.0) {
        return "(" + std::to_string(numerator) + "/" + std::to_string(denominator) + ")";
    } else {
        return std::to_string(numerator);
    }
}

Rational::Rational() : numerator(0), denominator(1) {
}

Rational operator+(const Rational &left, const Rational &right) {
    return Rational(left.numerator * right.denominator + left.denominator * right.numerator,
                    left.denominator * right.denominator);
}

Rational &operator+(Rational &left, const Rational &right) {
    left.numerator = left.numerator * right.denominator + left.denominator * right.numerator;
    left.denominator = left.denominator * right.denominator;
    return left;
}

Rational operator-(const Rational &left, const Rational &right) {
    return Rational(left.numerator * right.denominator - left.denominator * right.numerator,
                    left.denominator * right.denominator);
}

Rational &operator-(Rational &left, const Rational &right) {
    left.numerator = left.numerator * right.denominator - left.denominator * right.numerator;
    left.denominator = left.denominator * right.denominator;
    return left;
}

Rational operator*(const Rational &left, const Rational &right) {
    return Rational(left.numerator * right.numerator, left.denominator * right.denominator);
}

Rational &operator*(Rational &left, const Rational &right) {
    left.numerator *= right.numerator;
    left.denominator *= right.denominator;
    return left;
}

Rational operator/(const Rational &left, const Rational &right) {
    return Rational(left.numerator * right.denominator, left.denominator * right.numerator);
}

Rational &operator/(Rational &left, const Rational &right) {
    left.numerator *= right.denominator;
    left.denominator *= right.numerator;
    return left;
}
