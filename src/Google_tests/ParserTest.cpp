//
// Created by Nik Carlson on 21.12.2020.
//

#include "gtest/gtest.h"
#include "../Parser/Parser.h"

Parser parser;

class ParserTest : public ::testing::Test {
    ParserTest() {}

    ~ParserTest() {}

    void SetUp() { /* called before every test */ }

    void TearDown() { /* called after every test */ }
};

TEST(ParserTest, SIMPLE_PARSING) {
    ASSERT_STREQ(parser.parse("x+y")->to_str().c_str(), "x + y");
    ASSERT_STREQ(parser.parse("x+y+z")->to_str().c_str(), "x + y + z");
    ASSERT_STREQ(parser.parse("x*y")->to_str().c_str(), "x * y");
    ASSERT_STREQ(parser.parse("x*y*z")->to_str().c_str(), "x * y * z");
    ASSERT_STREQ(parser.parse("x*y+y*z+z*x")->to_str().c_str(), "x * y + y * z + z * x");
    ASSERT_STREQ(parser.parse("x*y*z+x*y*z+x*y*z")->to_str().c_str(), "x * y * z + x * y * z + x * y * z");
}