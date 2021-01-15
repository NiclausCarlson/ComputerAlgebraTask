//
// Created by Nik Carlson on 05.01.2021.
//

#include "FGLM.h"

FGLM::FGLM(std::vector<PolynomialTree> &old_basis, MonomialOrder *old_order, MonomialOrder *new_order) :
        old_basis(old_basis), old_order(old_order), new_order(new_order) {
}


std::string FGLM::get_in_maple_dsl() {
    std::string variable_set = "variablesSet := {x,y,z};";
    std::string old_basis_str = "oldBasis := [";
    std::string new_basis_str = "newBasis := [";
    for (auto i = old_basis.begin(); i != old_basis.end() - 1; ++i)
        old_basis_str += (*i)->to_str() + ", ";
    old_basis_str += (*(old_basis.end() - 1))->to_str() + "];\n\n";

    for (auto i = new_basis.begin(); i != new_basis.end() - 1; ++i)
        new_basis_str += (*i)->to_str() + ", ";
    new_basis_str += (*(new_basis.end() - 1))->to_str() + "];\n\n";
    std::string first_set = "firstSet := {solve(oldBasis, variablesSet)}\n";
    std::string second_set = "secondSet := {solve(newBasis, variablesSet)}\n";
    std::string checker = "print(\"Is same Ideals: \",((firstSet subset secondSet) and (secondSet subset firstSet)));\n\n";
    return variable_set + old_basis_str + new_basis_str + first_set + second_set + checker;
}

std::vector<PolynomialTree> FGLM::transform() {

    return std::vector<PolynomialTree>();
}

