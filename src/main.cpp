//
// Created by Nik Carlson on 04.12.2020.
//
#include<iostream>
#include "FGLM/FGLM.h"
#include "PolynomialOperations/MonomialOrder/Orders/Grlex.h"
#include <ctime>

using namespace std;

int main() {

    Parser parser;
    try {
        unsigned int start_time = clock();
        MonomialOrder *plex_order = new Plex({"x", "y", "z"});
        std::vector<std::string> old_basis_str{"z^6-z^2", "z^2+y", "x+z"};
        std::vector<Node *> old_basis;
        old_basis.reserve(old_basis_str.size());
        for (const auto &i: old_basis_str) {
            Node *tmp = parser.parse(i);
            old_basis.push_back(get_simplified(tmp, plex_order));
            std::string q = (*(old_basis.end() - 1))->to_str();
        }
        MonomialOrder *grlex_order = new Grlex({"x", "y", "z"});
        FGLM fglm = FGLM(old_basis, plex_order, grlex_order, {new Variable("x"),
                                                              new Variable("y"),
                                                              new Variable("z")});
        fglm.transform();
        std::string maple = fglm.get_in_maple_dsl();
        unsigned int end_time = clock();
        double search_time = (end_time - start_time)/1000.0;
        std::cout<<"Program finished in "<<search_time<<" second."<<std::endl;
        std::cout << maple << std::endl;
    } catch (ParseException &ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}