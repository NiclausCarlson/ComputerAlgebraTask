//
// Created by Nik Carlson on 05.01.2021.
//

#include "FGLM.h"
#include "../PolynomialOperations/MonomialOrder/Orders/Grlex.h"

#include <utility>


FGLM::FGLM(std::vector<PolynomialTree> &old_basis,
           MonomialOrder *old_order,
           MonomialOrder *new_order,
           std::vector<Variable *> variables_list) :
        old_basis(old_basis), old_order(old_order),
        new_order(new_order), variables_list(std::move(variables_list)),
        service_plex_order(new Plex({"x", "y", "z", "q"})) {
    std::vector<std::string> tmp;
    for (size_t i = 0; i < FREE_VARIABLES_QUANTITY; ++i) {
        std::string var = "@_" + std::to_string(i + 1);
        tmp.push_back(var);
        free_variables.push_back(new Variable(var));
        old_order->add_other_variable(var);
        new_order->add_other_variable(var);
        service_plex_order->add_other_variable(var);
    }
    linear_order = new Lex(tmp);
}


std::string FGLM::get_in_maple_dsl() {
    std::string order;
    auto is_plex = dynamic_cast<Plex *>(new_order);
    auto is_grlex = dynamic_cast<Grlex *>(new_order);
    if (is_plex != nullptr) order = "plex(";
    else if (is_grlex != nullptr) order = "grlex(";
    std::vector<std::string> v = new_order->get_variables();
    for (auto i = v.begin(); i != v.end() - 1; ++i)order += *i + ",";
    order += *(v.end() - 1);
    order += ")";

    std::string variable_set = "variablesSet := {x,y,z};\n\n";
    std::string old_basis_str = "oldBasis := [";
    std::string new_basis_str = "newBasis := [";
    for (auto i = old_basis.begin(); i != old_basis.end() - 1; ++i)
        old_basis_str += (*i)->to_str() + ", ";
    old_basis_str += (*(old_basis.end() - 1))->to_str() + "];\n";

    for (auto i = new_basis.begin(); i != new_basis.end() - 1; ++i)
        new_basis_str += (*i)->to_str() + ", ";
    new_basis_str += (*(new_basis.end() - 1))->to_str() + "];\n\n";
    std::string first_set = "firstSet := {solve(oldBasis, variablesSet)};\n";
    std::string second_set = "secondSet := {solve(newBasis, variablesSet)};\n";
    std::string is_right_order = "print(\"Is Groebner basis with current order: \", IsBasis(newBasis, " + order + "));";
    std::string checker = "print(\"Is same Ideals: \",((firstSet subset secondSet) and (secondSet subset firstSet)));\n\n";
    return variable_set + old_basis_str + new_basis_str + is_right_order + first_set + second_set + checker;
}

std::vector<PolynomialTree> FGLM::transform() {
    auto comparator = [&](Node *t1, Node *t2) { return new_order->compare(t1, t2); };
    std::vector<std::pair<Node *, Node *>> MBasis;
    std::vector<Node *> staircase;
    std::set<Node *, decltype(comparator)> set_of_nexts(comparator);
    Node *monom = new Constant(1.0);

    while (monom != nullptr) {
        if (!is_product(monom, staircase)) {
            //  std::string ms = monom->to_str();
            Node *v = get_normal_form(monom); // with respect to old_basis
            //   std::string vs = v->to_str();
            Node *relation = new Constant(0.0);
            if (get_linear_relation(v->clone(), MBasis, relation)) {
                std::string r = relation->to_str();
                Node *pol = sum(monom->clone(), relation, new_order);
                pol = get_simplified(pol, new_order);
                new_basis.push_back(pol);
                staircase.push_back(monom->clone());
            } else {
                delete relation;
                MBasis.emplace_back(monom, v);
                for (auto var : variables_list) {
                    Node *tmp = multiply_to_monomial(monom, var, new_order);
                    std::string q = tmp->to_str();
                    set_of_nexts.insert(tmp);
                }
            }
        }

        monom = nullptr;
        if (!set_of_nexts.empty()) {
            monom = *set_of_nexts.rbegin();
            set_of_nexts.erase(std::next(set_of_nexts.rbegin()).base());
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
    Node *normal_form = divide(polynomial, old_basis, old_order, service_plex_order).second;
    return normal_form;
}

bool FGLM::get_linear_relation(Node *v, std::vector<std::pair<Node *, Node *>> const &MBasis, Node *&relation) {
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

    to_system = sum(v->clone(), multiply_to_monomial(to_system,
                                                     new Constant(-1.0),
                                                     service_plex_order,
                                                     service_plex_order),
                    service_plex_order,
                    service_plex_order);


    std::string e = to_system->to_str();
    std::vector<Node *> monomials;
    to_system->get_monomials(monomials);
    std::vector<std::vector<Node *>> system_maker;
    std::vector<Node *> free_variables_equation;
    size_t eq_quantity = 0;
    for (size_t i = 0; i < monomials.size(); ++i) {
        auto c = dynamic_cast<Constant *>(monomials[i]);
        if (c != nullptr) {
            free_variables_equation.push_back(c);
            continue;
        }
        std::vector<Node *> equation;
        Node *divider = nullptr;
        std::vector<Node *> terms;
        monomials[i]->get_terms(terms);

        if ((*terms.rbegin())->to_str()[0] == '@') divider = normalize(terms.cbegin(), terms.cend() - 1);
        else divider = normalize(terms.cbegin(), terms.cend());
        if (divider == nullptr) {
            free_variables_equation.push_back(monomials[i]);
            continue;
        }
        while (i < monomials.size()) {
            c = dynamic_cast<Constant *>(monomials[i]);
            if (c != nullptr) {
                if (!equation.empty()) system_maker.push_back(equation);
                free_variables_equation.push_back(c);
                ++i;
                break;
            }

            Node *numerator = monomials[i];
            std::string numera = numerator->to_str();
            std::vector<Node *> numerators_terms;
            numerator->get_terms(numerators_terms);
            Node *normalized_numerator;
            std::string qq = (*numerators_terms.rbegin())->to_str();
            if ((*numerators_terms.rbegin())->to_str()[0] == '@')
                normalized_numerator = normalize(numerators_terms.cbegin(), numerators_terms.cend() - 1);
            else
                normalized_numerator = normalize(numerators_terms.cbegin(), numerators_terms.cend());

            if (normalized_numerator != nullptr && sumIfEquals(divider, normalized_numerator) != nullptr) {
                Node *tmp = divide_monomials(numerator, divider, service_plex_order, service_plex_order);
                std::string eee = tmp->to_str();
                equation.push_back(tmp);
                ++i;
                if (i >= monomials.size()) {
                    system_maker.push_back(equation);
                    ++eq_quantity;
                }
            } else {
                --i;
                system_maker.push_back(equation);
                ++eq_quantity;
                break;
            }
        }
    }
    if (!free_variables_equation.empty()) {
        system_maker.push_back(free_variables_equation);
        ++eq_quantity;
    }
//    for (const auto &i: system_maker) {
//        for (auto j: i) {
//            std::cout << j->to_str() << ' ';
//        }
//        std::cout << std::endl;
//    }
//    std::cout << "--------------------------\n";
    size_t dimention = std::max(eq_quantity, used_variables.size());
    mtl::dense2D<ld> system(dimention, dimention);
    mtl::dense_vector<ld> x(dimention), b(dimention);
    for (size_t i = 0; i < dimention; ++i) {
        for (size_t j = 0; j < dimention; ++j) system[i][j] = 0.0L;
        b[i] = 0.0L;
    }
    idx = 0;
    for (auto const &i: system_maker) {
        for (auto const &j : i) {
            auto is_const = dynamic_cast<Constant *>(j);
            auto is_var = dynamic_cast<Variable *>(j);
            auto is_mult = dynamic_cast<Multiplication *>(j);
            if (is_const != nullptr) b[idx] -= is_const->get_value();
            else if (is_var != nullptr) {
                std::string name = is_var->get_value();
                size_t ind = std::stoll(name.substr(2));
                system[idx][ind - 1] += 1.0L;
            } else if (is_mult != nullptr) {
                auto c = dynamic_cast<Constant *>(is_mult->getLeftNode());
                auto var = dynamic_cast<Variable *>(is_mult->getRightNode());
                std::string name = var->get_value();
                size_t ind = std::stoll(name.substr(2));
                system[idx][ind - 1] += c->get_value();
            }
        }
        ++idx;
    }

//    std::cout << "\n---------------------------------\n";
//    for (int i = 0; i < dimention; ++i) {
//        for (int j = 0; j < dimention; ++j) {
//            std::cout << system[i][j] << ' ';
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
//    std::cout << b << ' ';
//    std::cout << "\n---------------------------------\n";

    try {
        x = lu_solve(system, b);
    } catch (mtl::matrix_singular &t) {
        return false;
    }
    bool has_linear_relation = false;
    for (auto i: x) {
        ld abs = std::abs(i);
        if (!isnan(abs) && !isinf(abs) && abs >= eps) {
            has_linear_relation = true;
            break;
        }
    }
    if (!has_linear_relation) return false;
    idx = 0;
    for (int i = used_variables.size() - 1; i >= 0; --i) {
        Node *tmp = multiply_to_monomial(MBasis[i].first->clone(), new Constant(-x[idx]), service_plex_order,
                                         service_plex_order);
        relation = sum(relation, tmp, service_plex_order, service_plex_order);
        ++idx;
    }
    return true;
}

