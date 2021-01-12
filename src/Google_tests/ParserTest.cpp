//
// Created by Nik Carlson on 21.12.2020.
//

#include "gtest/gtest.h"
#include "../Parser/Parser.h"


class ParserTest : public ::testing::Test {
protected:
    Parser parser;

    ParserTest() = default;

    ~ParserTest() override = default;

    void SetUp() override { /* called before every test */ }

    void TearDown() override { /* called after every test */ }
};

TEST_F(ParserTest, SIMPLE_PARSING_TEST) {
    ASSERT_STREQ("x", parser.parse("x")->to_str().c_str());
    ASSERT_STREQ("xyz", parser.parse("xyz")->to_str().c_str());
    ASSERT_STREQ("x + y", parser.parse("x+y")->to_str().c_str());
    ASSERT_STREQ("x + y + z", parser.parse("x+y+z")->to_str().c_str());
    ASSERT_STREQ("x * y", parser.parse("x*y")->to_str().c_str());
    ASSERT_STREQ("x * y * z", parser.parse("x*y*z")->to_str().c_str());
    ASSERT_STREQ("x * y + y * z + z * x", parser.parse("x*y+y*z+z*x")->to_str().c_str());
    ASSERT_STREQ("x + -1.000000 * y + -1.000000 * z", parser.parse("x-y-z")->to_str().c_str());
    ASSERT_STREQ("x * y + -1.000000 * y * z + -1.000000 * z * x", parser.parse("x*y-y*z-z*x")->to_str().c_str());
    ASSERT_STREQ("x^2.000000", parser.parse("x^2")->to_str().c_str());
    ASSERT_STREQ("x^2.000000 * y^2.000000", parser.parse("x^2*y^2")->to_str().c_str());
    ASSERT_STREQ("x^2.000000 * y^2.000000 * z^233.000000", parser.parse("x^2*y^2*z^233")->to_str().c_str());
    ASSERT_STREQ("x^2.000000 + y^2.000000 + z^233.000000", parser.parse("x^2+y^2+z^233")->to_str().c_str());
    ASSERT_STREQ("-1.000000 * x", parser.parse("-x")->to_str().c_str());
    ASSERT_STREQ("-1.000000 * x + y", parser.parse("-x+y")->to_str().c_str());
    ASSERT_STREQ("-1.000000 * x * y", parser.parse("-x*y")->to_str().c_str());
    ASSERT_STREQ("-1.000000 * x * y * z", parser.parse("-x*y*z")->to_str().c_str());
}

TEST_F(ParserTest, ADVANCED_PARSING_TEST) {
    ASSERT_STREQ("x + y", parser.parse(" x        +                  y")->to_str().c_str());
    ASSERT_STREQ("x + y + z", parser.parse(" x   + y               +           z")->to_str().c_str());
    ASSERT_STREQ("x * y",
                 parser.parse("       x *                                                  y")->to_str().c_str());
    ASSERT_STREQ("x * y * z", parser.parse(" x * y * z")->to_str().c_str());
    ASSERT_STREQ("x * y + y * z + z * x",
                 parser.parse(" x  *   y    +     y      *      z     +  z * x")->to_str().c_str());
    ASSERT_STREQ("x^2.000000", parser.parse(" x ^  2   ")->to_str().c_str());
    ASSERT_STREQ("x^2.000000 * y^2.000000", parser.parse(" x ^  2   *     y        ^          2")->to_str().c_str());
    ASSERT_STREQ("x + -1.000000 * y + -1.000000 * z", parser.parse(" x -                     y-z")->to_str().c_str());
    ASSERT_STREQ("x * y + -1.000000 * y * z + -1.000000 * z * x", parser.parse("x * y-  y   * z- z *x ")->to_str().c_str());
    ASSERT_STREQ("x^2.000000 * y^2.000000 * z^233.000000", parser.parse("x^2  *y^ 2* z ^233")->to_str().c_str());
    ASSERT_STREQ("x^2.000000 + y^2.000000 + z^233.000000",
                 parser.parse("           x ^ 2 + y^2   +z^    233")->to_str().c_str());
    ASSERT_STREQ("-1.000000 * x", parser.parse("-       x")->to_str().c_str());
    ASSERT_STREQ("-1.000000 * x + y", parser.parse("- x +  y")->to_str().c_str());
    ASSERT_STREQ("-1.000000 * x + -1.000000 * y", parser.parse("-x -      y")->to_str().c_str());
}

TEST_F(ParserTest, NUMERIC_PARSING_TEST) {
    ASSERT_NEAR(1.000000, dynamic_cast<Constant *>(parser.parse("1"))->get_value(), eps);
    ASSERT_NEAR(2.000000, dynamic_cast<Constant *>(parser.parse("2"))->get_value(), eps);
    ASSERT_NEAR(4.000000, dynamic_cast<Constant *>(parser.parse("2*2"))->get_value(), eps);
    ASSERT_NEAR(16.000000, dynamic_cast<Constant *>(parser.parse("2*2*2*2"))->get_value(), eps);
    ASSERT_NEAR(36.000000, dynamic_cast<Constant *>(parser.parse("3*2*2*3"))->get_value(), eps);
    ASSERT_NEAR(4.000000, dynamic_cast<Constant *>(parser.parse("2*2*2/2"))->get_value(), eps);
    ASSERT_NEAR(0.21875, dynamic_cast<Constant *>(parser.parse("7/32"))->get_value(), eps);
    ASSERT_NEAR(0.875, dynamic_cast<Constant *>(parser.parse("7*4/32"))->get_value(), eps);
}

TEST_F(ParserTest, NUMBER_AS_COEFFICIENTS_TEST) {
    ASSERT_STREQ("1.000000 + 7.000000", parser.parse("1+7")->to_str().c_str());
    ASSERT_STREQ("5.000000 * x", parser.parse("5*x")->to_str().c_str());
    ASSERT_STREQ("20.000000 * x", parser.parse("4*5*x")->to_str().c_str());
    ASSERT_STREQ("5.000000 * x", parser.parse("4*5/4*x")->to_str().c_str());
    ASSERT_STREQ("7.000000 * xyz", parser.parse("7*xyz")->to_str().c_str());
    ASSERT_STREQ("7.000000 * x * 7.000000 * y * 7.000000 * z", parser.parse("7*x*7*y*7*z")->to_str().c_str());
    ASSERT_STREQ("7.000000 * xyz * 2.000000", parser.parse("7*xyz*2")->to_str().c_str());
    ASSERT_STREQ("17.000000 * x + y", parser.parse("17*x+y")->to_str().c_str());
    ASSERT_STREQ("17.000000 * x + 11.000000 * y", parser.parse("17*x+11*y")->to_str().c_str());
    ASSERT_STREQ("5.000000 * x + 4.000000 * y + 3.000000 * z", parser.parse("5*x+4*y+3*z")->to_str().c_str());
    ASSERT_STREQ("11.000000 * x * y", parser.parse("11*x*y")->to_str().c_str());
}