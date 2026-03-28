#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// We need to include the header under test
#include "catch2/internal/catch_decomposer.hpp"

namespace {

// A concrete implementation of ITransientExpression for testing purposes
class MockTransientExpression : public Catch::ITransientExpression {
public:
    MockTransientExpression(bool isBinaryExpression, bool result)
        : ITransientExpression(isBinaryExpression, result) {}

    MOCK_METHOD(void, streamReconstructedExpression, (std::ostream& os), (const, override));
};

// A simple concrete implementation that writes a known string
class ConcreteTransientExpression : public Catch::ITransientExpression {
public:
    ConcreteTransientExpression(bool isBinaryExpression, bool result, std::string text)
        : ITransientExpression(isBinaryExpression, result), m_text(std::move(text)) {}

    void streamReconstructedExpression(std::ostream& os) const override {
        os << m_text;
    }

private:
    std::string m_text;
};

// Test fixture
class ITransientExpressionTest_117 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that isBinaryExpression returns the value passed to constructor
TEST_F(ITransientExpressionTest_117, IsBinaryExpressionReturnsTrue_117) {
    ConcreteTransientExpression expr(true, false, "test");
    EXPECT_TRUE(expr.isBinaryExpression());
}

TEST_F(ITransientExpressionTest_117, IsBinaryExpressionReturnsFalse_117) {
    ConcreteTransientExpression expr(false, true, "test");
    EXPECT_FALSE(expr.isBinaryExpression());
}

// Test that getResult returns the value passed to constructor
TEST_F(ITransientExpressionTest_117, GetResultReturnsTrue_117) {
    ConcreteTransientExpression expr(false, true, "test");
    EXPECT_TRUE(expr.getResult());
}

TEST_F(ITransientExpressionTest_117, GetResultReturnsFalse_117) {
    ConcreteTransientExpression expr(true, false, "test");
    EXPECT_FALSE(expr.getResult());
}

// Test all four combinations of isBinaryExpression and result
TEST_F(ITransientExpressionTest_117, ConstructorBothTrue_117) {
    ConcreteTransientExpression expr(true, true, "");
    EXPECT_TRUE(expr.isBinaryExpression());
    EXPECT_TRUE(expr.getResult());
}

TEST_F(ITransientExpressionTest_117, ConstructorBothFalse_117) {
    ConcreteTransientExpression expr(false, false, "");
    EXPECT_FALSE(expr.isBinaryExpression());
    EXPECT_FALSE(expr.getResult());
}

// Test the operator<< friend function streams the reconstructed expression
TEST_F(ITransientExpressionTest_117, OperatorStreamOutputCallsStreamReconstructedExpression_117) {
    MockTransientExpression mockExpr(true, true);
    
    EXPECT_CALL(mockExpr, streamReconstructedExpression(::testing::_))
        .Times(1)
        .WillOnce([](std::ostream& os) {
            os << "mocked output";
        });

    std::ostringstream oss;
    oss << mockExpr;
    
    EXPECT_EQ(oss.str(), "mocked output");
}

// Test that operator<< returns the same ostream reference
TEST_F(ITransientExpressionTest_117, OperatorStreamReturnsOstream_117) {
    ConcreteTransientExpression expr(false, true, "hello");
    
    std::ostringstream oss;
    std::ostream& result = (oss << expr);
    
    EXPECT_EQ(&result, &oss);
}

// Test that the streamed output matches what streamReconstructedExpression writes
TEST_F(ITransientExpressionTest_117, OperatorStreamOutputMatchesExpression_117) {
    ConcreteTransientExpression expr(true, false, "1 == 2");
    
    std::ostringstream oss;
    oss << expr;
    
    EXPECT_EQ(oss.str(), "1 == 2");
}

// Test with empty string output
TEST_F(ITransientExpressionTest_117, OperatorStreamEmptyOutput_117) {
    ConcreteTransientExpression expr(false, false, "");
    
    std::ostringstream oss;
    oss << expr;
    
    EXPECT_EQ(oss.str(), "");
}

// Test with special characters in the output
TEST_F(ITransientExpressionTest_117, OperatorStreamSpecialCharacters_117) {
    ConcreteTransientExpression expr(true, true, "a < b && c > d\n\ttab");
    
    std::ostringstream oss;
    oss << expr;
    
    EXPECT_EQ(oss.str(), "a < b && c > d\n\ttab");
}

// Test copy constructor preserves values
TEST_F(ITransientExpressionTest_117, CopyConstructorPreservesValues_117) {
    ConcreteTransientExpression original(true, false, "copy test");
    ConcreteTransientExpression copy(original);
    
    EXPECT_EQ(copy.isBinaryExpression(), original.isBinaryExpression());
    EXPECT_EQ(copy.getResult(), original.getResult());
}

// Test that multiple streaming calls work correctly
TEST_F(ITransientExpressionTest_117, MultipleStreamCalls_117) {
    ConcreteTransientExpression expr1(true, true, "first");
    ConcreteTransientExpression expr2(false, false, "second");
    
    std::ostringstream oss;
    oss << expr1 << " and " << expr2;
    
    EXPECT_EQ(oss.str(), "first and second");
}

// Test that streamReconstructedExpression is called exactly once per operator<<
TEST_F(ITransientExpressionTest_117, StreamCalledExactlyOnce_117) {
    MockTransientExpression mockExpr(false, true);
    
    EXPECT_CALL(mockExpr, streamReconstructedExpression(::testing::_))
        .Times(1)
        .WillOnce([](std::ostream& os) {
            os << "once";
        });

    std::ostringstream oss;
    oss << mockExpr;
    
    EXPECT_EQ(oss.str(), "once");
}

// Test with long string output
TEST_F(ITransientExpressionTest_117, OperatorStreamLongOutput_117) {
    std::string longStr(10000, 'x');
    ConcreteTransientExpression expr(true, true, longStr);
    
    std::ostringstream oss;
    oss << expr;
    
    EXPECT_EQ(oss.str(), longStr);
    EXPECT_EQ(oss.str().size(), 10000u);
}

} // anonymous namespace
