//
// Created by Nik Carlson on 04.12.2020.
//

#ifndef COMPUTERALGEBRATASK_VARIABLE_H
#define COMPUTERALGEBRATASK_VARIABLE_H

#include "Operation.h"

class Variable : public Operation<char> {
private:
    char name;
public:
    Variable(char);

    char compute() override;

};


#endif //COMPUTERALGEBRATASK_VARIABLE_H
