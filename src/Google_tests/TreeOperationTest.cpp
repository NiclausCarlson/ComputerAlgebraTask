//
// Created by Nik Carlson on 27.12.2020.
//

#include "gtest/gtest.h"
#include "../Parser/Parser.h"


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
            get_expected_polynomials(std::vector<std::string>{"x"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("xyz")),
            get_expected_polynomials(std::vector<std::string>{"xyz"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x+y")),
            get_expected_polynomials(std::vector<std::string>{"x", "y"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x+y+z")),
            get_expected_polynomials(std::vector<std::string>{"x", "y", "z"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x*y")),
            get_expected_polynomials(std::vector<std::string>{"x*y"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x*y*z")),
            get_expected_polynomials(std::vector<std::string>{"x*y*z"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x*y+y*z+z*x")),
            get_expected_polynomials(std::vector<std::string>{"x*y", "y*z", "z*x"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x-y-z")),
            get_expected_polynomials(std::vector<std::string>{"x", "-y", "-z"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x*y-y*z-z*x")),
            get_expected_polynomials(std::vector<std::string>{"x*y", "-y*z", "-z*x"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x^2")),
            get_expected_polynomials(std::vector<std::string>{"x^2"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x^2*y^2")),
            get_expected_polynomials(std::vector<std::string>{"x^2*y^2"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x^2*y^2*z^233")),
            get_expected_polynomials(std::vector<std::string>{"x^2*y^2*z^233"})));

    ASSERT_TRUE(is_vector_equals(
            get_next_monomials(parser.parse("x^2+y^2+z^233")),
            get_expected_polynomials(std::vector<std::string>{"x^2", "y^2", "z^233"})));
}