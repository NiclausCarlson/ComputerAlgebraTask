//
// Created by Nik Carlson on 13.12.2020.
//

#ifndef COMPUTERALGEBRATASK_PARSER_H
#define COMPUTERALGEBRATASK_PARSER_H

#include <string>
#include "../PolynomialTree/PolynomialPrimitives/Node/Node.h"
#include "../PolynomialTree/PolynomialPrimitives/Operations/Operations/Sum.h"
#include "../PolynomialTree/PolynomialPrimitives/Operations/Operations/UnaryMinus.h"
#include "../Exceptions/ParserExceptions/WrongToken.h"
#include "../PolynomialTree/PolynomialPrimitives/Operations/Operations/Multiplication.h"
#include "../PolynomialTree/PolynomialPrimitives/Operands/Constant.h"
#include "../PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.h"
#include "../PolynomialTree/PolynomialPrimitives/Operands/Variable.h"

class Parser {
private:
    std::string str;
    int cur_pos;
    int length;
    PolynomialTree polynomial;

    enum class Token {
        CONST,
        VARIABLE,
        PLUS,
        MINUS,
        MULT,
        DIV,
        POW,
        END,
        DOT,
        ERROR
    };
    std::pair<Token, std::string> cur_token;
    std::pair<Token, std::string> prev_token;

    static Token getToken(char);

    void set_next_token();

    void tokenizer_helper(int (*)(int));

    static int isdigitOrIsDot(int);

    void skip_whitespaces();

    PolynomialTree parseExponential();

    PolynomialTree parseProductAndDivision();

    PolynomialTree parseSum();

    PolynomialTree parseUnaryAndNullaryOperations();

    void rightOperandChecker(Node *operand);

public:
    PolynomialTree parse(std::string);
};


#endif //COMPUTERALGEBRATASK_PARSER_H
