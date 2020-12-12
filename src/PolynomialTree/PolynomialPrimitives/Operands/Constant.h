
//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_CONSTANT_H
#define COMPUTERALGEBRATASK_CONSTANT_H


#include "../Node/Node.h"

class Constant : public Node {
private:
    const double value; // TODO: Maybe - double is bad idea
    const std::string stringValue;
public:
    std::string get_name() override;

    std::string to_str() override;

    double get_double_value() const;

    explicit Constant(double);

    virtual ~Constant() = default;
};


#endif //COMPUTERALGEBRATASK_CONSTANT_H
