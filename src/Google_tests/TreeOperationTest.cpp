//
// Created by Nik Carlson on 27.12.2020.
//

#include "gtest/gtest.h"
#include "../Parser/Parser.h"
#include "../PolynomialOperations/MonomialOrder/Orders/Lex.h"


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

//TEST_F(TreeOperationTest, SortMonomialTest) {
//    MonomialOrder *lexOrder = new Lex({"x", "y", "z"});
//    PolynomialTree tree = parser.parse("x");
//    lexOrder->sort_monomial(tree);
//    ASSERT_STREQ("x", tree->to_str().c_str());
//
//    tree = parser.parse("x+y");
//    lexOrder->sort_monomial(tree);
//    ASSERT_STREQ("x + y", tree->to_str().c_str());
//
//    tree = parser.parse("x^2*y^3");
//    lexOrder->sort_monomial(tree);
//    ASSERT_STREQ("x^2.000000 * y^3.000000", tree->to_str().c_str());
//
//    tree = parser.parse("z  * x * y *  z * z * z * y * x");
//    lexOrder->sort_monomial(tree);
//    ASSERT_STREQ("x ^ 2.000000 * y ^ 2.000000 * z ^ 4.000000", tree->to_str().c_str());
//}

//TEST_F(TreeOperationTest, LexOrderTest) {
//    MonomialOrder *lexOrder = new Lex({"x", "y", "z"});
//
//}
//
