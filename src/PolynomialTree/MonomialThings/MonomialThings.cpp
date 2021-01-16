//
// Created by Nik Carlson on 16.01.2021.
//

#include "MonomialThings.h"

Node *get_LT(PolynomialTree tree){
    std::vector<Node*> monomials;
    tree->get_monomials(monomials);
    if(!monomials.empty()) return *monomials.begin();
    //TODO: another exception
}