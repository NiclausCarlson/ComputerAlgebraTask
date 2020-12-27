
//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_CONSTANT_H
#define COMPUTERALGEBRATASK_CONSTANT_H


#include "../Node/Node.h"
#include "../../../RationalNumber/Rational.h"

class Constant : public Node {
private:
    const Rational value;
    const std::string stringValue;
public:
    explicit Constant(const Rational&);

    std::string to_str() override;

    void get_monomials(std::vector<Node*>& monomials) override;

    Rational get_value() const;

    virtual ~Constant() = default;
};


#endif //COMPUTERALGEBRATASK_CONSTANT_H
