#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include the header for the class under test
#include "catch2/internal/catch_decomposer.hpp"

// Since ITransientExpression has a protected destructor and virtual method,
// we need a concrete derived class for testing
class ConcreteTransientExpression : public Catch::ITransientExpression {
public:
    ConcreteTransientExpression(bool isBinaryExpression, bool result)
        : Catch::ITransientExpression(isBinaryExpression, result) {}

    ~ConcreteTransientExpression() override = default;
};

// A derived class that overrides streamReconstructedExpression
class CustomTransientExpression : public Catch::ITransientExpression {
public:
    CustomTransientExpression(bool isBinaryExpression, bool result)
        : Catch::ITransientExpression(isBinaryExpression, result) {}

    ~CustomTransientExpression() override = default;

    void streamReconstructedExpression(std::ostream& os) const override {
        os << "CustomExpression";
    }
};

// Test fixture
class ITransientExpressionTest_539 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructor correctly sets isBinaryExpression to true
TEST_F(ITransientExpressionTest_539, ConstructorSetsBinaryExpressionTrue_539) {
    ConcreteTransientExpression expr(true, false);
    EXPECT_TRUE(expr.isBinaryExpression());
}

// Test that constructor correctly sets isBinaryExpression to false
TEST_F(ITransientExpressionTest_539, ConstructorSetsBinaryExpressionFalse_539) {
    ConcreteTransientExpression expr(false, true);
    EXPECT_FALSE(expr.isBinaryExpression());
}

// Test that constructor correctly sets result to true
TEST_F(ITransientExpressionTest_539, ConstructorSetsResultTrue_539) {
    ConcreteTransientExpression expr(false, true);
    EXPECT_TRUE(expr.getResult());
}

// Test that constructor correctly sets result to false
TEST_F(ITransientExpressionTest_539, ConstructorSetsResultFalse_539) {
    ConcreteTransientExpression expr(true, false);
    EXPECT_FALSE(expr.getResult());
}

// Test both isBinaryExpression and result set to true
TEST_F(ITransientExpressionTest_539, BothTrueTrue_539) {
    ConcreteTransientExpression expr(true, true);
    EXPECT_TRUE(expr.isBinaryExpression());
    EXPECT_TRUE(expr.getResult());
}

// Test both isBinaryExpression and result set to false
TEST_F(ITransientExpressionTest_539, BothFalseFalse_539) {
    ConcreteTransientExpression expr(false, false);
    EXPECT_FALSE(expr.isBinaryExpression());
    EXPECT_FALSE(expr.getResult());
}

// Test default streamReconstructedExpression outputs expected message
TEST_F(ITransientExpressionTest_539, DefaultStreamReconstructedExpression_539) {
    ConcreteTransientExpression expr(true, true);
    std::ostringstream oss;
    expr.streamReconstructedExpression(oss);
    std::string output = oss.str();
    EXPECT_EQ(output, "Some class derived from ITransientExpression without overriding streamReconstructedExpression");
}

// Test that overridden streamReconstructedExpression works correctly
TEST_F(ITransientExpressionTest_539, OverriddenStreamReconstructedExpression_539) {
    CustomTransientExpression expr(false, true);
    std::ostringstream oss;
    expr.streamReconstructedExpression(oss);
    std::string output = oss.str();
    EXPECT_EQ(output, "CustomExpression");
}

// Test copy constructor preserves isBinaryExpression
TEST_F(ITransientExpressionTest_539, CopyConstructorPreservesIsBinaryExpression_539) {
    ConcreteTransientExpression original(true, false);
    ConcreteTransientExpression copy(original);
    EXPECT_TRUE(copy.isBinaryExpression());
    EXPECT_FALSE(copy.getResult());
}

// Test copy constructor preserves result
TEST_F(ITransientExpressionTest_539, CopyConstructorPreservesResult_539) {
    ConcreteTransientExpression original(false, true);
    ConcreteTransientExpression copy(original);
    EXPECT_FALSE(copy.isBinaryExpression());
    EXPECT_TRUE(copy.getResult());
}

// Test copy assignment operator
TEST_F(ITransientExpressionTest_539, CopyAssignmentOperator_539) {
    ConcreteTransientExpression expr1(true, true);
    ConcreteTransientExpression expr2(false, false);
    expr2 = expr1;
    EXPECT_TRUE(expr2.isBinaryExpression());
    EXPECT_TRUE(expr2.getResult());
}

// Test that streamReconstructedExpression writes to an empty stream
TEST_F(ITransientExpressionTest_539, StreamReconstructedExpressionEmptyStream_539) {
    ConcreteTransientExpression expr(false, false);
    std::ostringstream oss;
    EXPECT_TRUE(oss.str().empty());
    expr.streamReconstructedExpression(oss);
    EXPECT_FALSE(oss.str().empty());
}

// Test polymorphic behavior through base pointer
TEST_F(ITransientExpressionTest_539, PolymorphicStreamBehavior_539) {
    CustomTransientExpression customExpr(true, false);
    Catch::ITransientExpression* basePtr = &customExpr;

    std::ostringstream oss;
    basePtr->streamReconstructedExpression(oss);
    EXPECT_EQ(oss.str(), "CustomExpression");
}

// Test that default stream message via base pointer for non-overridden class
TEST_F(ITransientExpressionTest_539, DefaultStreamViaBasePointer_539) {
    ConcreteTransientExpression concreteExpr(false, true);
    Catch::ITransientExpression* basePtr = &concreteExpr;

    std::ostringstream oss;
    basePtr->streamReconstructedExpression(oss);
    EXPECT_EQ(oss.str(), "Some class derived from ITransientExpression without overriding streamReconstructedExpression");
}

// Test that isBinaryExpression is constexpr-compatible (at runtime check)
TEST_F(ITransientExpressionTest_539, IsBinaryExpressionReturnType_539) {
    ConcreteTransientExpression expr(true, true);
    bool result = expr.isBinaryExpression();
    EXPECT_TRUE(result);
}

// Test that getResult is constexpr-compatible (at runtime check)
TEST_F(ITransientExpressionTest_539, GetResultReturnType_539) {
    ConcreteTransientExpression expr(false, false);
    bool result = expr.getResult();
    EXPECT_FALSE(result);
}

// Test multiple writes to the same stream
TEST_F(ITransientExpressionTest_539, MultipleStreamWrites_539) {
    ConcreteTransientExpression expr(true, true);
    std::ostringstream oss;
    expr.streamReconstructedExpression(oss);
    expr.streamReconstructedExpression(oss);

    std::string expected = "Some class derived from ITransientExpression without overriding streamReconstructedExpression"
                           "Some class derived from ITransientExpression without overriding streamReconstructedExpression";
    EXPECT_EQ(oss.str(), expected);
}
