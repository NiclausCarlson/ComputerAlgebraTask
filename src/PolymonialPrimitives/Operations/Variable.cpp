//
// Created by Nik Carlson on 04.12.2020.
//

#include "Variable.h"

Variable::Variable(char name) : name(name) {
}


char Variable::compute() {
    return name;
}