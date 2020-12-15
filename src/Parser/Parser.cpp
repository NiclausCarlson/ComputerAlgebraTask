//
// Created by Nik Carlson on 13.12.2020.
//

#include "Parser.h"

PolynomialTree Parser::parse(std::string toParse) {
    str = std::move(toParse);
    cur_pos = 0;
    length = str.size();
    cur_token = std::make_pair(Token::ERROR, "");

    return polynomial;
}

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
        cur_token = std::make_pair(Token::CONST, str.substr(prev_pos, cur_pos - prev_pos - 1));
    } else if (isalpha(str[cur_pos])) {
        tokenizer_helper(isalpha);
        cur_token = std::make_pair(Token::VARIABLE, str.substr(prev_pos, cur_pos - prev_pos - 1));
    } else if (str[cur_pos] == '*' || str[cur_pos] == '+' || str[cur_pos] == '^') {
        cur_token = std::make_pair(Token::BINARY_OPERATOR, std::to_string(str[cur_pos]));
        cur_pos++;
    } else if (str[cur_pos] == '-' || str[cur_pos] == '+' || str[cur_pos] == '^') {
        cur_token = std::make_pair(Token::UNARY_OPERATOR, std::to_string(str[cur_pos]));
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

PolynomialTree Parser::parseConstAndVariables() {
    set_next_token();
    Node *node;
    if (cur_token.first == Token::CONST) {

    }
    return nullptr;
}

