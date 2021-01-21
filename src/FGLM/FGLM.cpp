//
// Created by Nik Carlson on 05.01.2021.
//

#include "FGLM.h"


FGLM::FGLM(std::vector<PolynomialTree> &old_basis,
           MonomialOrder *old_order,
           MonomialOrder *new_order,
           std::vector<Variable *> &variables_list) :
        old_basis(old_basis), old_order(old_order),
        new_order(new_order), variables_list(variables_list) {}


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
    std::vector<std::pair<Node *, Node *>> MBasis;
    std::vector<Node *> staircase;
    std::set<Node *> set_of_nexts;//нужно как-то добавить компаратор(так, чтобы мономы шли в обратном порядке)
    Node *monom = new Constant(1.0);

    while (monom != nullptr) {
        if (!is_product(monom, staircase)) {
            Node *v = get_normal_form(monom); // with respect to old_basis
            Node *relation;
            if (has_linear_relation(v, MBasis, relation)) {
                Node *pol = new Sum(monom, relation);
                pol = get_simplified(pol, new_order);
                new_basis.push_back(pol);// в алгоритме ставится в начало списка. Нужно, либо чуть-чуть подправить алгоритм, либо использовать другую структуру даных
                staircase.push_back(monom);// в алгоритме ставится в начало списка
            } else {
                MBasis.emplace_back(monom, v);// в алгоритме пара ставится в начало MBasis
                insert_nexts(monom, set_of_nexts);// with respect to new order
            }
        }

        monom = nullptr;
        if (!set_of_nexts.empty()) {
            monom = *set_of_nexts.begin();
            set_of_nexts.erase(monom);
        }
    }

    return new_basis;
}

bool FGLM::is_product(Node *monom, std::vector<Node *> const &staircase) {
    if (!staircase.empty()) {
        Node *tmp = monom->clone();
        for (auto p: staircase) {
            // до тех пор, пока tmp делится на p
            // мы делим tmp на p
            // Видимо, нужно делоить до тех пор, пока остаток равен нулю.
            // Но, с другой стороны, tmp - это моном, и staircase - это мономы, мб стоит написать функцию
            // divide_if_divides для мономов?
        }
        auto result = dynamic_cast<Constant *>(tmp);
        if (result != nullptr && result->get_value() == 1.0) return true;
    }
    return false;
}

PolynomialTree FGLM::get_normal_form(PolynomialTree polynomial) {
    // normal_form - о сути, остаток от деления
    Node *normal_form = divide(polynomial, old_basis, old_order).second;
    return normal_form;
}

bool FGLM::has_linear_relation(Node *v, std::vector<std::pair<Node *, Node *>> const &MBasis, Node *&relation) {
    mtl::dense2D<double> A(2, 2);
    A[0][0] = 2;
    A[0][1] = 1;
    A[1][0] = 1;
    A[1][1] = 2;
    mtl::dense_vector<double> x(2), b(2);
    b[0] = 0;
    b[1] = 0;
    x = lu_solve(A, b);
    std::cout << x << std::endl;
    return false;
}

void FGLM::insert_nexts(Node *v, std::set<Node *> &set_of_nexts) {
    for (auto var : variables_list)
        set_of_nexts.insert(multiply_to_monomial(v, var, old_order));
}
