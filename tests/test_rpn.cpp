#include "gtest/gtest.h"
#include "../include/rpn.h"
TEST(RPNTest, PowerOperation) {
    EXPECT_EQ(evaluate_rpn("2 3 ^"), 8);
}

TEST(RPNTest, ModuloOperation) {
    EXPECT_EQ(evaluate_rpn("10 3 %"), 1);
}

TEST(RPNTest, FactorialOperation) {
    EXPECT_EQ(evaluate_rpn("5 !"), 120);
}

TEST(RPNTest, SquareRoot) {
    EXPECT_EQ(evaluate_rpn("16 sqrt"), 4);
}

TEST(RPNTest, TrigonometricFunctions) {
    EXPECT_NEAR(evaluate_rpn("0 sin"), 0, 0.001);
    EXPECT_NEAR(evaluate_rpn("0 cos"), 1, 0.001);
}

TEST(RPNTest, Constants) {
    EXPECT_NEAR(evaluate_rpn("pi"), 3.14159, 0.001);
    EXPECT_NEAR(evaluate_rpn("e"), 2.71828, 0.001);
}

TEST(RPNTest, StackOperations) {
    EXPECT_EQ(evaluate_rpn("5 dup +"), 10);
    EXPECT_EQ(evaluate_rpn("3 4 swap -"), 1); // 4 - 3 = 1
}
