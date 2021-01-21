//
// Created by Nik Carlson on 27.12.2020.
//

#include <algorithm>
#include "gtest/gtest.h"
#include "../Parser/Parser.h"
#include "../PolynomialOperations/MonomialOrder/Orders/Lex.h"
#include "../PolynomialOperations/MonomialOrder/Orders/Plex.h"


class TreeOperationTest : public ::testing::Test {
protected:
    Parser parser;

    TreeOperationTest() = default;

    ~TreeOperationTest() override = default;

    void SetUp() override { /* called before every test */ }

    void TearDown() override { /* called after every test */ }

    static bool is_vector_equals(const std::vector<Node *> &v1, const std::vector<Node *> &v2) {
        if (v1.size() == v2.size()) {
            for (size_t i = 0; i < v1.size(); ++i) {
                if (v1[i]->to_str() != v2[i]->to_str()) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    static std::vector<PolynomialTree> get_next_monomials(PolynomialTree const &tree) {
        std::vector<PolynomialTree> monomials;
        tree->get_monomials(monomials);
        return monomials;
    }

    static std::vector<PolynomialTree> get_next_terms(PolynomialTree const &tree) {
        std::vector<PolynomialTree> terms;
        tree->get_terms(terms);
        return terms;
    }

    void set_monomials(std::string &monomial, std::vector<Node *> &monomials) {
        if (!monomials.empty()) monomials.clear();
        Node *tree = parser.parse(monomial);
        tree->get_monomials(monomials);
    }

    bool compare(std::string const &p1, std::string const &p2, MonomialOrder *order) {
        Node* t1 = parser.parse(p1);
        Node* t2 = parser.parse(p2);
        return order->compare(t1, t2);
    }

    std::vector<PolynomialTree> get_expected_polynomials(const std::vector<std::string> &monomials) {
        std::vector<PolynomialTree> expected;
        expected.reserve(monomials.size());
        for (const auto &i: monomials) {
            expected.push_back(parser.parse(i));
        }
        return expected;
    }
};

TEST_F(TreeOperationTest, GetMonomialsTest) {

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x")),
            get_expected_polynomials({"x"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("xyz")),
            get_expected_polynomials({"xyz"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x+y")),
            get_expected_polynomials({"x", "y"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x+y+z")),
            get_expected_polynomials({"x", "y", "z"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x*y")),
            get_expected_polynomials({"x*y"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x*y*z")),
            get_expected_polynomials({"x*y*z"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x*y+y*z+z*x")),
            get_expected_polynomials({"x*y", "y*z", "z*x"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x-y-z")),
            get_expected_polynomials({"x", "-y", "-z"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x*y-y*z-z*x")),
            get_expected_polynomials({"x*y", "-y*z", "-z*x"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x^2")),
            get_expected_polynomials({"x^2"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x^2*y^2")),
            get_expected_polynomials({"x^2*y^2"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x^2*y^2*z^233")),
            get_expected_polynomials({"x^2*y^2*z^233"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x^2+y^2+z^233")),
            get_expected_polynomials({"x^2", "y^2", "z^233"})));
}

TEST_F(TreeOperationTest, GetTermsTest) {
    ASSERT_TRUE(is_vector_equals(
            get_next_terms(parser.parse("5")),
            get_expected_polynomials({"5.000000"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_terms(parser.parse("x")),
            get_expected_polynomials({"x"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_terms(parser.parse("x*y")),
            get_expected_polynomials({"x", "y"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_terms(parser.parse("x*y*z")),
            get_expected_polynomials({"x", "y", "z"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_terms(parser.parse("x*y*z")),
            get_expected_polynomials({"x", "y", "z"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_terms(parser.parse("x^2*y^2")),
            get_expected_polynomials({"x^2", "y^2"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_terms(parser.parse("x^2*y^2*z^233")),
            get_expected_polynomials({"x^2", "y^2", "z^233"})));

}

TEST_F(TreeOperationTest, LexSortMonomialTest) {
    MonomialOrder *lex_order = new Lex({"x", "y", "z"});
    PolynomialTree tree = parser.parse("x");
    lex_order->sort_monomial(tree);
    ASSERT_STREQ("x", tree->to_str().c_str());

    tree = parser.parse("x*y");
    lex_order->sort_monomial(tree);
    ASSERT_STREQ("x * y", tree->to_str().c_str());

    tree = parser.parse("x^2*y^3");
    lex_order->sort_monomial(tree);
    ASSERT_STREQ("x^2.000000 * y^3.000000", tree->to_str().c_str());

    tree = parser.parse("z  * x * y *  z * z * z * y * x");
    lex_order->sort_monomial(tree);
    ASSERT_STREQ("x^2.000000 * y^2.000000 * z^4.000000", tree->to_str().c_str());

    tree = parser.parse("y*y*y*z*z*z*x*y*z*y");
    lex_order->sort_monomial(tree);
    ASSERT_STREQ("x * y^5.000000 * z^4.000000", tree->to_str().c_str());

    tree = parser.parse("17*y*y*z");
    lex_order->sort_monomial(tree);
    ASSERT_STREQ("17.000000 * y^2.000000 * z", tree->to_str().c_str());

    tree = parser.parse("2*x*y*y*y*x*25*z");
    lex_order->sort_monomial(tree);
    ASSERT_STREQ("50.000000 * x^2.000000 * y^3.000000 * z", tree->to_str().c_str());

    tree = parser.parse("-5 * x * x * 5");
    lex_order->sort_monomial(tree);
    ASSERT_STREQ("-25.000000 * x^2.000000", tree->to_str().c_str());

    tree = parser.parse("-5 * x * x * -5");
    lex_order->sort_monomial(tree);
    ASSERT_STREQ("25.000000 * x^2.000000", tree->to_str().c_str());

}

TEST_F(TreeOperationTest, LexOrderCompareTest) {
    MonomialOrder *lex_order = new Lex({"x", "y", "z"});

    std::string monomial1 = "x";
    std::string monomial2 = "y";
    ASSERT_TRUE(compare(monomial1, monomial2, lex_order));

    monomial1 = "x";
    monomial2 = "x";
    ASSERT_TRUE(compare(monomial1, monomial2, lex_order));

    monomial1 = "x^2";
    monomial2 = "x^2";
    ASSERT_TRUE(compare(monomial1, monomial2, lex_order));

    monomial1 = "x^2*y";
    monomial2 = "z";
    ASSERT_TRUE(compare(monomial1, monomial2, lex_order));

    monomial1 = "-x";
    monomial2 = "-x";
    ASSERT_TRUE(compare(monomial1, monomial2, lex_order));

    monomial1 = "-x*y";
    monomial2 = "x";
    ASSERT_TRUE(compare(monomial1, monomial2, lex_order));

    monomial1 = "x*y*z^2";
    monomial2 = "-x*z";
    ASSERT_TRUE(compare(monomial1, monomial2, lex_order));

    monomial1 = "-y^25*z^25";
    monomial2 = "y*z";
    ASSERT_TRUE(compare(monomial1, monomial2, lex_order));

    monomial1 = "x";
    monomial2 = "-x*y";
    ASSERT_TRUE(!compare(monomial1, monomial2, lex_order));

    monomial1 = "-x*z";
    monomial2 = "x*y*z^2";
    ASSERT_TRUE(!compare(monomial1, monomial2, lex_order));

}

TEST_F(TreeOperationTest, PlexOrderCompareTest) {
    MonomialOrder *lex_order = new Plex({"x", "y", "z"});
}

TEST_F(TreeOperationTest, PlexSimplifyTest) {
    MonomialOrder *lex_order = new Plex({"x", "y", "z"});
    std::vector<Node *> v1, v2;
    std::string p1 = "x";
    std::string p2 = "y";
}
