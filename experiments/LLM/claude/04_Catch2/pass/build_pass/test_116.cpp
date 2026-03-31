#include <gtest/gtest.h>
#include <sstream>

// Include the header under test
#include "./TestProjects/Catch2/src/catch2/internal/catch_decomposer.hpp"

// Since ITransientExpression has a pure virtual function (streamReconstructedExpression),
// we need a concrete subclass for testing purposes.
class ConcreteTransientExpression : public Catch::ITransientExpression {
public:
    ConcreteTransientExpression(bool isBinaryExpression, bool result)
        : ITransientExpression(isBinaryExpression, result) {}

    void streamReconstructedExpression(std::ostream& os) const override {
        os << "ConcreteExpression";
    }
};

// Test fixture
class ITransientExpressionTest_116 : public ::testing::Test {
protected:
    // Helper to create instances
};

// Test that getResult returns true when constructed with result=true
TEST_F(ITransientExpressionTest_116, GetResultReturnsTrueWhenConstructedWithTrue_116) {
    ConcreteTransientExpression expr(false, true);
    EXPECT_TRUE(expr.getResult());
}

// Test that getResult returns false when constructed with result=false
TEST_F(ITransientExpressionTest_116, GetResultReturnsFalseWhenConstructedWithFalse_116) {
    ConcreteTransientExpression expr(false, false);
    EXPECT_FALSE(expr.getResult());
}

// Test that getResult returns true when isBinaryExpression is true and result is true
TEST_F(ITransientExpressionTest_116, GetResultTrueWithBinaryExpressionTrue_116) {
    ConcreteTransientExpression expr(true, true);
    EXPECT_TRUE(expr.getResult());
}

// Test that getResult returns false when isBinaryExpression is true and result is false
TEST_F(ITransientExpressionTest_116, GetResultFalseWithBinaryExpressionTrue_116) {
    ConcreteTransientExpression expr(true, false);
    EXPECT_FALSE(expr.getResult());
}

// Test isBinaryExpression returns true when constructed with isBinaryExpression=true
TEST_F(ITransientExpressionTest_116, IsBinaryExpressionReturnsTrueWhenSetTrue_116) {
    ConcreteTransientExpression expr(true, false);
    EXPECT_TRUE(expr.isBinaryExpression());
}

// Test isBinaryExpression returns false when constructed with isBinaryExpression=false
TEST_F(ITransientExpressionTest_116, IsBinaryExpressionReturnsFalseWhenSetFalse_116) {
    ConcreteTransientExpression expr(false, true);
    EXPECT_FALSE(expr.isBinaryExpression());
}

// Test copy constructor preserves getResult
TEST_F(ITransientExpressionTest_116, CopyConstructorPreservesResult_116) {
    ConcreteTransientExpression original(true, true);
    ConcreteTransientExpression copy(original);
    EXPECT_EQ(original.getResult(), copy.getResult());
}

// Test copy constructor preserves isBinaryExpression
TEST_F(ITransientExpressionTest_116, CopyConstructorPreservesIsBinaryExpression_116) {
    ConcreteTransientExpression original(true, false);
    ConcreteTransientExpression copy(original);
    EXPECT_EQ(original.isBinaryExpression(), copy.isBinaryExpression());
}

// Test copy assignment preserves getResult
TEST_F(ITransientExpressionTest_116, CopyAssignmentPreservesResult_116) {
    ConcreteTransientExpression expr1(false, true);
    ConcreteTransientExpression expr2(true, false);
    expr2 = expr1;
    EXPECT_TRUE(expr2.getResult());
}

// Test copy assignment preserves isBinaryExpression
TEST_F(ITransientExpressionTest_116, CopyAssignmentPreservesIsBinaryExpression_116) {
    ConcreteTransientExpression expr1(false, true);
    ConcreteTransientExpression expr2(true, false);
    expr2 = expr1;
    EXPECT_FALSE(expr2.isBinaryExpression());
}

// Test all four combinations of (isBinaryExpression, result)
TEST_F(ITransientExpressionTest_116, AllCombinationsFalseFalse_116) {
    ConcreteTransientExpression expr(false, false);
    EXPECT_FALSE(expr.isBinaryExpression());
    EXPECT_FALSE(expr.getResult());
}

TEST_F(ITransientExpressionTest_116, AllCombinationsFalseTrue_116) {
    ConcreteTransientExpression expr(false, true);
    EXPECT_FALSE(expr.isBinaryExpression());
    EXPECT_TRUE(expr.getResult());
}

TEST_F(ITransientExpressionTest_116, AllCombinationsTrueFalse_116) {
    ConcreteTransientExpression expr(true, false);
    EXPECT_TRUE(expr.isBinaryExpression());
    EXPECT_FALSE(expr.getResult());
}

TEST_F(ITransientExpressionTest_116, AllCombinationsTrueTrue_116) {
    ConcreteTransientExpression expr(true, true);
    EXPECT_TRUE(expr.isBinaryExpression());
    EXPECT_TRUE(expr.getResult());
}

// Test streamReconstructedExpression produces output
TEST_F(ITransientExpressionTest_116, StreamReconstructedExpressionWritesToStream_116) {
    ConcreteTransientExpression expr(false, true);
    std::ostringstream oss;
    expr.streamReconstructedExpression(oss);
    EXPECT_FALSE(oss.str().empty());
}

// Test that multiple calls to getResult are consistent
TEST_F(ITransientExpressionTest_116, GetResultIsConsistentAcrossMultipleCalls_116) {
    ConcreteTransientExpression expr(true, true);
    EXPECT_TRUE(expr.getResult());
    EXPECT_TRUE(expr.getResult());
    EXPECT_TRUE(expr.getResult());
}

// Test that multiple calls to isBinaryExpression are consistent
TEST_F(ITransientExpressionTest_116, IsBinaryExpressionIsConsistentAcrossMultipleCalls_116) {
    ConcreteTransientExpression expr(false, false);
    EXPECT_FALSE(expr.isBinaryExpression());
    EXPECT_FALSE(expr.isBinaryExpression());
    EXPECT_FALSE(expr.isBinaryExpression());
}

// Test self-assignment
TEST_F(ITransientExpressionTest_116, SelfAssignmentPreservesState_116) {
    ConcreteTransientExpression expr(true, true);
    expr = expr;
    EXPECT_TRUE(expr.getResult());
    EXPECT_TRUE(expr.isBinaryExpression());
}
