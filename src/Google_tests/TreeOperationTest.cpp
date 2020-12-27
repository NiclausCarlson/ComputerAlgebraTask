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
};

TEST_F(TreeOperationTest, GetMonomialsTest){

}