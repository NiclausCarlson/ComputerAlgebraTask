
//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_CONSTANT_H
#define COMPUTERALGEBRATASK_CONSTANT_H


#include "../Node/Node.h"
#include "../../../RationalNumber/RationalNumber.h"

class Constant : public Node {
private:
    const RationalNumber value;
    const std::string stringValue;
public:
    std::string get_name() override;

    std::string to_str() override;

    RationalNumber get_value() const;

    explicit Constant(RationalNumber);

    virtual ~Constant() = default;
};


#endif //COMPUTERALGEBRATASK_CONSTANT_H
