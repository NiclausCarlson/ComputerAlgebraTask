//
// Created by Nik Carlson on 31.12.2020.
//

#ifndef COMPUTERALGEBRATASK_UTILS_H
#define COMPUTERALGEBRATASK_UTILS_H

#include <string>
#include "../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../PolynomialTree/PolynomialPrimitives/Operations/Operations/UnaryMinus.h"
#include "../PolynomialTree/PolynomialPrimitives/Operands/Constant.h"
#include "../PolynomialTree/PolynomialPrimitives/Operands/Variable.h"
#include "../PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.h"

inline std::string get_instance(PolynomialTree tree) {
    if (dynamic_cast<UnaryMinus *>( tree) != nullptr) return "UnaryMinus";
    if (dynamic_cast<Constant *>( tree) != nullptr) return "Constant";
    if (dynamic_cast<Variable *>( tree) != nullptr) return "Variable";
    if (dynamic_cast<Exponentiation *>( tree) != nullptr) return "Exponentiation";
    //TODO: Throw Exception
}

#endif //COMPUTERALGEBRATASK_UTILS_H
