
//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_CONSTANT_H
#define COMPUTERALGEBRATASK_CONSTANT_H


#include "../Node/Node.h"

typedef long double ld;

const ld eps = 1e10;

inline ld absolute(ld number) {
    return number <= 0 ? -number : number;
}

class Constant : public Node {
private:
    const ld value;
    const std::string stringValue;
public:

    explicit Constant(ld);

    std::string to_str() override;

    void get_monomials(std::vector<Node *> &monomials) override;

    ld get_value() const;

    virtual ~Constant() = default;
};


#endif //COMPUTERALGEBRATASK_CONSTANT_H
