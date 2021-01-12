//
// Created by Nik Carlson on 13.12.2020.
//

#include "Parser.h"
#include "../Exceptions/ParserExceptions/UnsupportedOperation.h"
#include "../Exceptions/ParserExceptions/LostOperand.h"
#include "../Exceptions/ParserExceptions/InvalidArgument.h"

void Parser::tokenizer_helper(int (*func)(int)) {
    while (func(str[cur_pos]) && cur_pos < length) {
        cur_pos++;
    }
}

void Parser::set_next_token() {
    skip_whitespaces();
    prev_token = cur_token;

    if (cur_pos >= length) {
        cur_token = std::make_pair(Token::END, "");
        return;
    }
    int prev_pos = cur_pos;
    if (isdigit(str[cur_pos])) {
        tokenizer_helper(isdigitOrIsDot);
        cur_token = std::make_pair(Token::CONST, str.substr(prev_pos, cur_pos - prev_pos));
    } else if (isalpha(str[cur_pos])) {
        tokenizer_helper(isalpha);
        cur_token = std::make_pair(Token::VARIABLE, str.substr(prev_pos, cur_pos - prev_pos));
    } else if (str[cur_pos] == '*' || str[cur_pos] == '+' || str[cur_pos] == '^' ||
               str[cur_pos] == '-' || str[cur_pos] == '/') {
        cur_token = std::make_pair(getToken(str[cur_pos]), std::string(1, str[cur_pos]));
        cur_pos++;
    } else {
        cur_token = std::make_pair(Token::ERROR, "Unsupported operation");
    }
}

void Parser::skip_whitespaces() {
    while (cur_pos < length && isspace(str[cur_pos])) {
        cur_pos++;
    }
}

PolynomialTree Parser::parseUnaryAndNullaryOperations() {
    set_next_token();
    Node *right;
    Constant *constant;
    switch (cur_token.first) {
        case Token::CONST:
            set_next_token();
            return new Constant(stold(prev_token.second));
        case Token::VARIABLE:
            set_next_token();
            return new Variable(prev_token.second);
        case Token::MINUS:
            right = parseExponential();
            if (prev_token.first == Token::CONST) {
                constant = dynamic_cast<Constant *>(right);
                return new Constant(-constant->get_value());
            } else {
                return new Multiplication(new Constant(-1.0), right);
            }

        case Token::END:
            return nullptr;
        default:
            cur_token = std::make_pair(Token::ERROR, "can't parse token");
            return nullptr;
    }
}

PolynomialTree Parser::parseExponential() {
    auto *left = parseUnaryAndNullaryOperations();
    auto *left_checker = dynamic_cast<Constant *>(left);
    Constant *right_number;
    while (true) {
        if (cur_token.first == Token::POW) {
            if (left_checker != nullptr) {
                throw UnsupportedOperation(cur_token.second, "Number exponentiation is prohibit.");
            }
            right_number = dynamic_cast<Constant *>(parseUnaryAndNullaryOperations());
            if (right_number == nullptr) {
                throw UnsupportedOperation(cur_token.second, "Polynomial exponentiation is prohibit.");
            }
            if (absolute(right_number->get_value() - 1) > eps) {
                throw UnsupportedOperation(cur_token.second, "Invalid monomial power.");
            }
            left = (Node *) (new Exponentiation(left, right_number));
        } else {
            return left;
        }
    }
}

PolynomialTree Parser::parseProductAndDivision() {
    auto *left = parseExponential();
    Node *right;
    Constant *left_number, *right_number;
    ld n;
    while (true) {
        left_number = dynamic_cast<Constant *>(left);
        switch (cur_token.first) {
            case Token::MULT:
                right = parseExponential();
                right_number = dynamic_cast<Constant *>(right);
                if (left_number != nullptr && right_number != nullptr) {
                    n = left_number->get_value() * right_number->get_value();
                    left = (Node *) (new Constant(n));
                } else {
                    left = (Node *) (new Multiplication(left, right));
                }
                continue;
            case Token::DIV:
                right = parseExponential();
                right_number = dynamic_cast<Constant *>(right);
                if (left_number != nullptr && right_number != nullptr) {
                    n = left_number->get_value() / right_number->get_value();
                    left = (Node *) (new Constant(n));
                } else if (left_number != nullptr) {
                    n = 1 / left_number->get_value();
                    left = (Node *) (new Multiplication((Node *) (new Constant(n)), right));
                } else {
                    throw UnsupportedOperation(cur_token.second, "Polynomial division is prohibit");
                }
                continue;
            default:
                if (cur_token.first == Token::ERROR) {
                    throw WrongToken(cur_token.second);
                }
                return left;
        }
    }
}

PolynomialTree Parser::parseSum() {
    auto *left = parseProductAndDivision();
    Node *right;
    while (true) {
        switch (cur_token.first) {
            case Token::PLUS:
                right = parseProductAndDivision();
                rightOperandChecker(right);
                left = (Node *) (new Sum(left, right));
                break;
            case Token::MINUS:
                right = parseProductAndDivision();
                rightOperandChecker(right);
                left = (Node *) (new Sum(left,
                                         (Node *) (new Multiplication(new Constant(-1.0), right))));
                break;
            default:
                if (cur_token.first == Token::ERROR) {
                    throw WrongToken(cur_token.second);
                }
                return left;
        }
    }
}

PolynomialTree Parser::parse(std::string toParse) {
    str = std::move(toParse);
    cur_pos = 0;
    length = str.size();
    cur_token = std::make_pair(Token::ERROR, "");
    polynomial = parseSum();
    return polynomial;
}

Parser::Token Parser::getToken(char op) {
    if (op == '+') return Token::PLUS;
    if (op == '-') return Token::MINUS;
    if (op == '*') return Token::MULT;
    if (op == '/') return Token::DIV;
    if (op == '^') return Token::POW;
    return Token::ERROR;
}

void Parser::rightOperandChecker(Node *operand) {
    if (operand == nullptr) {
        throw LostOperand(prev_token.second);
    }
}

int Parser::isdigitOrIsDot(int ch) {
    return isdigit(ch) || (ch == '.');
}
