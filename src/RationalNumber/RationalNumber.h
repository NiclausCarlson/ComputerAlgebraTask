//
// Created by Nik Carlson on 18.12.2020.
//

#ifndef COMPUTERALGEBRATASK_RATIONALNUMBER_H
#define COMPUTERALGEBRATASK_RATIONALNUMBER_H

#include <string>

typedef long long ll;

class RationalNumber {
private:
    ll numerator;
    ll denominator;
    std::string string_value;
public:
    RationalNumber(ll, ll);

    std::string to_str() const;
};


#endif //COMPUTERALGEBRATASK_RATIONALNUMBER_H
