//
// Created by Nik Carlson on 18.01.2021.
//

#include "gtest/gtest.h"
#include "../Parser/Parser.h"
#include "../PolynomialOperations/MonomialOrder/MonomialOrder.h"
#include "../PolynomialOperations/Simplify/Equals.h"
#include "../PolynomialOperations/ArithmeticOperations/ArithmeticOperations.h"
#include "../PolynomialOperations/MonomialOrder/Orders/Lex.h"

class PolynomialOperationsTest : public ::testing::Test {
protected:
    Parser parser;
    MonomialOrder *lex_order = new Lex({"x", "y", "z"});
    PolynomialTree t1{}, t2{}, t3{};
    std::vector<Node *> v1, v2;

    PolynomialOperationsTest() = default;

    ~PolynomialOperationsTest() override = default;

    void SetUp() override { /* called before every test */ }

    void TearDown() override { /* called after every test */ }

    static void fill_vector(PolynomialTree tree, std::vector<Node *> &monomials) {
        monomials.clear();
        tree->get_monomials(monomials);
    }

    void fill_vector(const std::vector<std::string> &polynomials, std::vector<Node *> &to_fill) {
        to_fill.clear();
        for (const auto &i: polynomials) {
            Node *a = parser.parse(i);
            to_fill.push_back(a);
        }
    }

    static bool is_equals(std::vector<Node *> &v1, std::vector<Node *> &v2) {
        return equals(v1, v2);
    }

    bool is_equals(Node *first, Node *second) {
        fill_vector(first, v1);
        fill_vector(second, v2);
        return equals(v1, v2);
    }

};

TEST_F(PolynomialOperationsTest, EqualsTest) {
    t1 = parser.parse("x");
    t2 = parser.parse("x");
    ASSERT_TRUE(is_equals(t1, t2));

    t1 = parser.parse("4*x");
    t2 = parser.parse("4*x");
    ASSERT_TRUE(is_equals(t1, t2));

    t1 = parser.parse("4*x");
    t2 = parser.parse("2*x");
    ASSERT_TRUE(!is_equals(t1, t2));

    t1 = parser.parse("4*x + 1");
    t2 = parser.parse("4*x + 1");
    ASSERT_TRUE(is_equals(t1, t2));

    t1 = parser.parse("4*x*y*z + 5x*y*z*q*r");
    t2 = parser.parse("4*x*y*z + 5x*y*z*q*r");
    ASSERT_TRUE(is_equals(t1, t2));

    t1 = parser.parse("4*x*y*z - 5x*y*z*q*r");
    t2 = parser.parse("4*x*y*z + 5x*y*z*q*r");
    ASSERT_TRUE(!is_equals(t1, t2));

    t1 = parser.parse("4*x^2");
    t2 = parser.parse("4*x^2");
    ASSERT_TRUE(is_equals(t1, t2));

    t1 = parser.parse("-4*x");
    t2 = parser.parse("4*x");
    ASSERT_TRUE(!is_equals(t1, t2));

    t1 = parser.parse("-4*x");
    t2 = parser.parse("-4*x");
    ASSERT_TRUE(is_equals(t1, t2));

    t1 = parser.parse("4*x*y^3");
    t2 = parser.parse("4*x");
    ASSERT_TRUE(!is_equals(t1, t2));

    t1 = parser.parse("4*x*y^3");
    t2 = parser.parse("4*x*y^3");
    ASSERT_TRUE(is_equals(t1, t2));

    t1 = parser.parse("x*y^3*z+25*y");
    t2 = parser.parse("x*y^3*z+25*y");
    ASSERT_TRUE(is_equals(t1, t2));

    t1 = parser.parse("x*y^3*z+25*y");
    t2 = parser.parse("x*y^3*z-25*y");
    ASSERT_TRUE(!is_equals(t1, t2));
}

TEST_F(PolynomialOperationsTest, SumTest) {
    t1 = parser.parse("x");
    t2 = parser.parse("x");
    t3 = parser.parse("2*x");

    PolynomialTree s = sum(t1, t2, lex_order);
    ASSERT_TRUE(is_equals(t3, s));

    t1 = parser.parse("x+y");
    t2 = parser.parse("x");
    t3 = parser.parse("2*x+y");
    s = sum(t1, t2, lex_order);
    ASSERT_TRUE(is_equals(t3, s));

    t1 = parser.parse("x+y");
    t2 = parser.parse("x");
    t3 = parser.parse("2*x+y");
    s = sum(t1, t2, lex_order);
    ASSERT_TRUE(is_equals(t3, s));

    t1 = parser.parse("x+y");
    t2 = parser.parse("x+y");
    t3 = parser.parse("2*x+2*y");
    s = sum(t1, t2, lex_order);
    ASSERT_TRUE(is_equals(t3, s));

    t1 = parser.parse("x*y");
    t2 = parser.parse("x");
    t3 = parser.parse("x*y + x");
    s = sum(t1, t2, lex_order);
    ASSERT_TRUE(is_equals(t3, s));

    t1 = parser.parse("x*y + x");
    t2 = parser.parse("x");
    t3 = parser.parse("x*y + 2*x");
    s = sum(t1, t2, lex_order);
    ASSERT_TRUE(is_equals(t3, s));

    t1 = parser.parse("-x+y");
    t2 = parser.parse("x");
    t3 = parser.parse("y");
    s = sum(t1, t2, lex_order);
    std::string t = s->to_str();
    ASSERT_TRUE(is_equals(t3, s));

    t1 = parser.parse("x-y");
    t2 = parser.parse("y");
    t3 = parser.parse("x");
    s = sum(t1, t2, lex_order);
    ASSERT_TRUE(is_equals(t3, s));

    t1 = parser.parse("x^2+y^2");
    t2 = parser.parse("x");
    t3 = parser.parse("x^2+x+y^2");
    s = sum(t1, t2, lex_order);
    ASSERT_TRUE(is_equals(t3, s));

    t1 = parser.parse("x^2+y^2");
    t2 = parser.parse("x^2+y^2");
    t3 = parser.parse("2*x^2+2*y^2");
    s = sum(t1, t2, lex_order);
    ASSERT_TRUE(is_equals(t3, s));
}

TEST_F(PolynomialOperationsTest, DivideTest) {
    std::pair<std::vector<Node *>, PolynomialTree> d;
    std::vector<Node *> f;
    t1 = parser.parse("x");
    t2 = parser.parse("x");
    fill_vector({"1"}, f);
    d = divide(t1, {t2}, lex_order);
    ASSERT_TRUE(is_equals(d.first, f) && d.second == nullptr);

    t1 = parser.parse("x^3");
    t2 = parser.parse("x");
    fill_vector({"x^2"}, f);
    d = divide(t1, {t2}, lex_order);
    ASSERT_TRUE(is_equals(d.first, f) && d.second == nullptr);

//    t1 = parser.parse("x+y");
//    t2 = parser.parse("x");
//    fill_vector({"1"}, f);
//    d = divide(t1, {t2}, lex_order);
//    t3 = parser.parse("y");
//    ASSERT_TRUE(is_equals(d.first, f) && is_equals(d.second, t3));
//
//    t1 = parser.parse("x + y");
//    t2 = parser.parse("x + y");
//    fill_vector({"1"}, f);
//    d = divide(t1, {t2}, lex_order);
//    ASSERT_TRUE(is_equals(d.first, f) && d.second == nullptr);
//
//    t1 = parser.parse("x^3+3*x^2-7*x+10");
//    t2 = parser.parse("x^2+6*x");
//    fill_vector({"1"}, f);
//    d = divide(t1, {t2}, lex_order);
//    t3 = parser.parse("43");
//    ASSERT_TRUE(is_equals(d.first, f) && is_equals(d.second, t3));

//    t1 = parser.parse("x");
//    t2 = parser.parse("x");
//    fill_vector({"1"}, f);
//    d = divide(t1, {t2}, lex_order);
//    ASSERT_TRUE(is_equals(d.first, f) && d.second == nullptr);
}
