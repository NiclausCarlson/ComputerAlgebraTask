//
// Created by Nik Carlson on 12.12.2020.
//

#ifndef COMPUTERALGEBRATASK_VARIABLE_H
#define COMPUTERALGEBRATASK_VARIABLE_H


#include "../Node/Node.h"

class Variable : public Node {
private:
    std::string name = "variable";
    const std::string value;
public:
    std::string get_name() override;

    std::string to_str() override;

    std::string get_value() const;

    void get_monomials(std::vector<Node*>& monomials) override;

    explicit Variable(std::string);

    virtual ~Variable() = default;
};


#endif //COMPUTERALGEBRATASK_VARIABLE_H
