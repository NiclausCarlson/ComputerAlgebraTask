//
// Created by Nik Carlson on 13.12.2020.
//

#include "Parser.h"


void Parser::tokenizer_helper(int (*func)(int)) {
    while (func(str[cur_pos]) && cur_pos < length) {
        cur_pos++;
    }
}

void Parser::set_next_token() {
    skip_whitespaces();
    if (cur_pos >= length) {
        cur_token = std::make_pair(Token::END, "");
        return;
    }
    int prev_pos = cur_pos;
    if (isdigit(str[cur_pos])) {
        tokenizer_helper(isdigit);
        cur_token = std::make_pair(Token::CONST, str.substr(prev_pos, cur_pos - prev_pos));
    } else if (isalpha(str[cur_pos])) {
        tokenizer_helper(isalpha);
        cur_token = std::make_pair(Token::VARIABLE, str.substr(prev_pos, cur_pos - prev_pos));
    } else if (str[cur_pos] == '*' || str[cur_pos] == '+' || str[cur_pos] == '^' ||
               str[cur_pos] == '-' || str[cur_pos] == '\\') {
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
    auto token_copy = cur_token;
    switch (cur_token.first) {
        case Token::CONST:
            set_next_token();
            return new Constant(RationalNumber(stol(token_copy.second)));
        case Token::VARIABLE:
            set_next_token();
            return new Variable(token_copy.second);
        default:
            set_next_token();
            return nullptr;
    }
}

PolynomialTree Parser::parseExponential() {
    auto *left = parseUnaryAndNullaryOperations();
    while (true) {
        if (cur_token.first == Token::POW) {
            left = (Node *) (new Exponentiation(left, parseUnaryAndNullaryOperations()));
        } else {
            return left;
        }
    }
}

PolynomialTree Parser::parseProductAndDivision() {
    auto *left = parseExponential();
    Node *right, *left_checker, *right_checker;
    while (true) {
        switch (cur_token.first) {
            case Token::DOT:
                left = (Node *) (new Multiplication(left, parseProductAndDivision()));
                continue;
            case Token::DIV:
                right = parseExponential();
                left_checker = dynamic_cast<Constant * >(left);
                right_checker = dynamic_cast<Constant * >(right);
                if (left_checker != nullptr && right_checker != nullptr) {
                    //left = поделим два рациональных числа друг на друга
                } else {
                    throw NotNumberDivision(cur_token.second);
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
    while (true) {
        switch (cur_token.first) {
            case Token::PLUS:
                left = (Node *) (new Sum(left, parseProductAndDivision()));
                break;
            case Token::MINUS:
                left = (Node *) (new Sum((Node *) (new UnaryMinus(left)),
                                         parseProductAndDivision()));
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
    if (op == '*') return Token::DOT;
    if (op == '\\') return Token::DIV;
    if (op == '^')return Token::POW;
    return Token::ERROR;
}
