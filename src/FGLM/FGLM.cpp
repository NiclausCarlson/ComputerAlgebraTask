//
// Created by Nik Carlson on 05.01.2021.
//

#include "FGLM.h"

#include <utility>


FGLM::FGLM(std::vector<PolynomialTree> &old_basis,
           MonomialOrder *old_order,
           MonomialOrder *new_order,
           std::vector<Variable *> variables_list) :
        old_basis(old_basis), old_order(old_order),
        new_order(new_order), variables_list(std::move(variables_list)),
        service_plex_order(new Plex({"x", "y", "z", "q"})) {
    for (size_t i = 0; i < FREE_VARIABLES_QUANTITY; ++i) {
        std::string var = "@_" + std::to_string(i + 1);
        free_variables.push_back(new Variable(var));
        old_order->add_other_variable(var);
        new_order->add_other_variable(var);
        service_plex_order->add_other_variable(var);
    }
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
    auto comparator = [&](Node *t1, Node *t2) { return !new_order->compare(t1, t2); };
    std::vector<std::pair<Node *, Node *>> MBasis;
    std::vector<Node *> staircase;
    std::set<Node *, decltype(comparator)> set_of_nexts(comparator);
    Node *monom = new Constant(1.0);

    while (monom != nullptr) {
        if (!is_product(monom, staircase)) {
            Node *v = get_normal_form(monom); // with respect to old_basis
            std::string ms = monom->to_str();
            std::string vs = v->to_str();
            Node *relation = nullptr;
            if (has_linear_relation(v, MBasis, relation)) {
                Node *pol = new Sum(monom, relation);
                pol = get_simplified(pol, new_order);
                new_basis.push_back(pol);
                staircase.push_back(monom);
            } else {
                MBasis.emplace_back(monom, v);
                for (auto var : variables_list){
                    Node* tmp = multiply_to_monomial(monom, var, new_order);
                    std::string q = tmp->to_str();
                    set_of_nexts.insert(tmp);
                }
            }
        }

        monom = nullptr;
        if (!set_of_nexts.empty()) {
            monom = *set_of_nexts.begin();
            set_of_nexts.erase(set_of_nexts.begin());
        }
    }

    return new_basis;
}

bool FGLM::is_product(Node *monom, std::vector<Node *> const &staircase) {
    //перебираем staircase c конца
    if (!staircase.empty()) {
        Node *tmp = monom->clone();
        for (auto p = staircase.rbegin(); p != staircase.rend(); ++p) {
            Node *div_res = divide_monomials(tmp, *p, service_plex_order);
            if (div_res != nullptr) tmp = div_res;
        }
        auto result = dynamic_cast<Constant *>(tmp);
        if (result != nullptr && result->get_value() == 1.0) return true;
    }
    return false;
}

PolynomialTree FGLM::get_normal_form(PolynomialTree polynomial) {
    // normal_form - о сути, остаток от деления
    Node *normal_form = divide(polynomial, old_basis, old_order, service_plex_order).second;
    return normal_form;
}

bool FGLM::has_linear_relation(Node *v, std::vector<std::pair<Node *, Node *>> const &MBasis, Node *&relation) {
    size_t idx = 0;
    Node *to_system = new Constant(0.0);
    std::vector<Node *> used_variables;
    for (auto p = MBasis.rbegin(); p != MBasis.rend(); ++p) {
        to_system = sum(to_system,
                        multiply_to_monomial(p->second,
                                             free_variables[idx],
                                             service_plex_order,
                                             service_plex_order),
                        service_plex_order,
                        service_plex_order);
        std::string l = to_system->to_str();
        used_variables.push_back(free_variables[idx]);
        ++idx;
    }
    if (used_variables.empty()) return false;

    to_system = sum(v, multiply_to_monomial(to_system,
                                            new Constant(-1.0),
                                            service_plex_order,
                                            service_plex_order),
                    service_plex_order,
                    service_plex_order);

    std::string e = to_system->to_str();
    std::vector<Node *> monomials;
    to_system->get_monomials(monomials);
    std::vector<std::vector<Node *>> system_maker;
    for (size_t i = 0; i < monomials.size(); ++i) {
        std::vector<Node *> equation;
        Node *to_divide = nullptr;
        std::vector<Node *> terms;
        monomials[i]->get_terms(terms);
        for (auto j: terms) {
            auto *const_checker = dynamic_cast<Constant *>(j);
            auto *variable_checker = dynamic_cast<Variable *>(j);
            if (const_checker == nullptr &&
                (variable_checker == nullptr || variable_checker->get_value()[0] != '@')) {
                if (to_divide == nullptr) to_divide = j->clone();
                else to_divide = multiply_to_monomial(to_divide, j, service_plex_order, service_plex_order);
            }
        }
        if (to_divide == nullptr) equation.push_back(monomials[i]);
        else {
            while (i < monomials.size()) {
                Node *div_res = divide_monomials(monomials[i], to_divide, service_plex_order, service_plex_order);
                if (div_res == nullptr) {
                    --i;
                    break;
                } else equation.push_back(div_res);
                ++i;
            }
        }
        bool is_good_equation = false;
        for (auto j: equation) {
            std::string instance = get_instance(j);
            if (instance != "Constant") is_good_equation = true;
        }
        if (!is_good_equation) return false;
        system_maker.push_back(equation);
    }

    std::vector<std::string> linear_order_var;
    linear_order_var.reserve(used_variables.size());
    for (auto p: used_variables) linear_order_var.push_back(p->to_str());
    MonomialOrder *linear_order = new Lex(linear_order_var);
    auto comp = [&linear_order](Node *t1, Node *t2) { return linear_order->compare(t1, t2); };
    size_t max_equations_length = 0;
    for (auto &i: system_maker) {
        max_equations_length = std::max(max_equations_length, i.size());
        std::sort(i.begin(), i.end(), comp);
        for (auto j: i) {
            std::string e = j->to_str();
        }
    }
    mtl::dense2D<ld> system(system_maker.size(), max_equations_length);
    //надо константы направо перенести
    mtl::dense_vector<ld> x(free_variables.size()), b(free_variables.size());
    for (size_t i = 0; i < free_variables.size(); ++i) b[i] = 0;

    size_t row = 0, column = 0;
    for (auto const &eq: system_maker) {
        column = 0;
        for (size_t i = 0; i < eq.size(); ++i) {
            std::string q = eq[i]->to_str();
            auto *var = dynamic_cast<Variable *>(eq[i]);
            auto *mul = dynamic_cast<Multiplication *>(eq[i]);
            if (var != nullptr) system[row][i] = 1.0L;
            else if (mul != nullptr) {
                auto *c = dynamic_cast<Constant *>(mul->getLeftNode());
                system[row][i] = c->get_value();
            } else {
                auto *c = dynamic_cast<Constant *>(eq[i]);
                b[row] += c->get_value();
            }
            ++column;
        }
        if (eq.size() < max_equations_length) {
            for (; column < max_equations_length; ++column) system[row][column] = 0.0L;
        }
        ++row;
    }

    x = lu_solve(system, b);
    bool has_linear_relation = false;
    for (auto i: x) {
        if (std::abs(i) >= eps) {
            has_linear_relation = true;
            break;
        }
    }
    if (!has_linear_relation) return false;
    for (size_t i = 0; i < free_variables.size(); ++i) {
        Node *tmp = multiply_to_monomial(MBasis[i].first, new Constant(x[i]), service_plex_order);
        relation = sum(relation, tmp, service_plex_order);
    }
    return true;

//    mtl::dense2D<double> A(2, 2);
//    A[0][0] = 2;
//    A[0][1] = 1;
//    A[1][0] = 1;
//    A[1][1] = 2;
//    mtl::dense_vector<double> x(2), b(2);
//    b[0] = 0;
//    b[1] = 0;
//    x = lu_solve(A, b);
//    std::cout << x << std::endl;
}

