//
// Created by Nik Carlson on 12.12.2020.
//

#include "AbstractUnaryOperation.h"

#include <utility>

AbstractUnaryOperation::AbstractUnaryOperation(Node *operand, std::string type)
        : operand(operand), type(std::move(type)) {
}

std::string AbstractUnaryOperation::get_name() {
    return type;
}

Node const *AbstractUnaryOperation::getOperand() const {
    return operand;
}

Node *AbstractUnaryOperation::getOperand() {
    return operand;
}

std::string AbstractUnaryOperation::to_str() {
    //проверка типа выражения
    //если оператор - ^, то operand, type
    //иначе:
    return type + operand->to_str();
}
