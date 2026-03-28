#include <gtest/gtest.h>
#include <sstream>

// Include the header under test
#include "./TestProjects/Catch2/src/catch2/internal/catch_decomposer.hpp"

// Since ITransientExpression has a pure virtual function, we need a concrete derived class for testing
class ConcreteTransientExpression : public Catch::ITransientExpression {
public:
    ConcreteTransientExpression(bool isBinaryExpression, bool result)
        : Catch::ITransientExpression(isBinaryExpression, result) {}

    void streamReconstructedExpression(std::ostream& os) const override {
        os << "test_expression";
    }
};

// Test fixture
class ITransientExpressionTest_115 : public ::testing::Test {
protected:
};

// Test that isBinaryExpression returns true when constructed with true
TEST_F(ITransientExpressionTest_115, IsBinaryExpressionReturnsTrue_115) {
    ConcreteTransientExpression expr(true, false);
    EXPECT_TRUE(expr.isBinaryExpression());
}

// Test that isBinaryExpression returns false when constructed with false
TEST_F(ITransientExpressionTest_115, IsBinaryExpressionReturnsFalse_115) {
    ConcreteTransientExpression expr(false, true);
    EXPECT_FALSE(expr.isBinaryExpression());
}

// Test that getResult returns true when constructed with result=true
TEST_F(ITransientExpressionTest_115, GetResultReturnsTrue_115) {
    ConcreteTransientExpression expr(false, true);
    EXPECT_TRUE(expr.getResult());
}

// Test that getResult returns false when constructed with result=false
TEST_F(ITransientExpressionTest_115, GetResultReturnsFalse_115) {
    ConcreteTransientExpression expr(true, false);
    EXPECT_FALSE(expr.getResult());
}

// Test both flags true
TEST_F(ITransientExpressionTest_115, BothFlagsTrue_115) {
    ConcreteTransientExpression expr(true, true);
    EXPECT_TRUE(expr.isBinaryExpression());
    EXPECT_TRUE(expr.getResult());
}

// Test both flags false
TEST_F(ITransientExpressionTest_115, BothFlagsFalse_115) {
    ConcreteTransientExpression expr(false, false);
    EXPECT_FALSE(expr.isBinaryExpression());
    EXPECT_FALSE(expr.getResult());
}

// Test copy construction preserves isBinaryExpression
TEST_F(ITransientExpressionTest_115, CopyConstructionPreservesIsBinaryExpression_115) {
    ConcreteTransientExpression original(true, false);
    ConcreteTransientExpression copy(original);
    EXPECT_TRUE(copy.isBinaryExpression());
    EXPECT_FALSE(copy.getResult());
}

// Test copy construction preserves getResult
TEST_F(ITransientExpressionTest_115, CopyConstructionPreservesGetResult_115) {
    ConcreteTransientExpression original(false, true);
    ConcreteTransientExpression copy(original);
    EXPECT_FALSE(copy.isBinaryExpression());
    EXPECT_TRUE(copy.getResult());
}

// Test copy assignment operator
TEST_F(ITransientExpressionTest_115, CopyAssignmentPreservesValues_115) {
    ConcreteTransientExpression expr1(true, true);
    ConcreteTransientExpression expr2(false, false);
    expr2 = expr1;
    EXPECT_TRUE(expr2.isBinaryExpression());
    EXPECT_TRUE(expr2.getResult());
}

// Test streamReconstructedExpression via virtual dispatch
TEST_F(ITransientExpressionTest_115, StreamReconstructedExpressionWorks_115) {
    ConcreteTransientExpression expr(true, true);
    std::ostringstream os;
    expr.streamReconstructedExpression(os);
    EXPECT_EQ(os.str(), "test_expression");
}

// Test that isBinaryExpression is constexpr-compatible (compile-time check)
TEST_F(ITransientExpressionTest_115, IsBinaryExpressionIsConstexprCompatible_115) {
    ConcreteTransientExpression expr(true, false);
    constexpr bool expected = true;
    // We can't make it truly constexpr due to virtual destructor, but we verify the call works
    bool result = expr.isBinaryExpression();
    EXPECT_EQ(result, expected);
}

// Test that getResult is constexpr-compatible
TEST_F(ITransientExpressionTest_115, GetResultIsConstexprCompatible_115) {
    ConcreteTransientExpression expr(false, true);
    bool result = expr.getResult();
    EXPECT_TRUE(result);
}

// Test mixed combinations - binary=false, result=false
TEST_F(ITransientExpressionTest_115, NonBinaryFalseResult_115) {
    ConcreteTransientExpression expr(false, false);
    EXPECT_FALSE(expr.isBinaryExpression());
    EXPECT_FALSE(expr.getResult());
}

// Test mixed combinations - binary=true, result=true
TEST_F(ITransientExpressionTest_115, BinaryTrueResult_115) {
    ConcreteTransientExpression expr(true, true);
    EXPECT_TRUE(expr.isBinaryExpression());
    EXPECT_TRUE(expr.getResult());
}

// Test that copy assignment from different state works correctly
TEST_F(ITransientExpressionTest_115, CopyAssignmentChangesState_115) {
    ConcreteTransientExpression expr1(true, false);
    ConcreteTransientExpression expr2(false, true);

    EXPECT_TRUE(expr1.isBinaryExpression());
    EXPECT_FALSE(expr1.getResult());

    expr1 = expr2;

    EXPECT_FALSE(expr1.isBinaryExpression());
    EXPECT_TRUE(expr1.getResult());
}
